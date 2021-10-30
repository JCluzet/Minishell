/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:01:28 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/30 02:25:07 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_close_cmd(t_sdata *sdata, char *line)
{
	if (!line)
	{
		deallocate_sdata(sdata);
		usage_exit(NULL);
	}
	return (0);
}

int	shell_loop(t_sdata *sdata)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("\033[33m$ ➜\033[00m ");
		add_history(line);
		if (line[0] == 0 || empty_str(line) || check_line(line) == -1)
			continue ;
		sdata->nb_of_cmds = check_line(line);
		sdata->cmds = parse_line(sdata, line);
		execution_dispatcher(sdata, sdata->cmds);
		deallocate_cmd_list(sdata->cmds);
		sdata->cmds = NULL;
		if (is_close_cmd(sdata, line))
			break;
	}
	return (sdata->lrval);
}

int		check_line(char *line)
{
	if (quotes_check(line) == -1 || !line || redir_check(line) == -1)
		return(-1);
	if (pipe_check(line) == -1)
	{
		printf("minishell: parse error near '|'\n");
		return (-1);
	}
	return (pipe_check(line));
}

int		redir_check(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			if (!cmd[i + 2] || cmd[i + 2] == '<' || cmd[i + 2] == '<')
			{
				printf("minishell: parse error near '<'\n");
				return (-1);
			}
		}
		if (cmd[i] == '>' && cmd[i + 1] == '>')
		{
			if (!cmd[i + 2] || cmd[i + 2] == '>' || cmd[i + 2] == '<' )
			{
				printf("minishell: parse error near '>'\n");
				return (-1);
			}
		}
		i++;
	}
	return(0);
}
