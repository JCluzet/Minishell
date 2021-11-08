/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:01:28 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/08 20:14:33 by amine            ###   ########.fr       */
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
		if (line == NULL)
			break ;
		add_history(line);
		if (line[0] == 0 || empty_str(line) || check_line(line) == -1)
			continue ;
		sdata->nb_of_cmds = check_line(line);
		sdata->cmds = parse_line(sdata, line);
		if (!sdata->cmds->cmd)
			continue ;
		execution_dispatcher(sdata, sdata->cmds);
		deallocate_cmd_list(sdata->cmds);
		sdata->cmds = NULL;
		if (is_close_cmd(sdata, line))
			break ;
	}
	return (sdata->lrval);
}

int		check_line(char *line)
{
	if (quotes_check(line) == -1 || !line || redir_check(line) == -1)
		return (-1);
	if (pipe_check(line) == -1)
	{
		printf("minishell: parse error near '|'\n");
		return (-1);
	}
	return (pipe_check(line));
}

int		redir_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if ((cmd[i] == '>' && cmd[i + 1] == '>') || (cmd[i] == '<' && cmd[i + 1] == '<'))
		{
			if (!cmd[skip_blank(cmd + i + 2) + i + 2]
				|| cmd[skip_blank(cmd + i + 2) + i + 2] == '>'
				|| cmd[skip_blank(cmd + i + 2) + i + 2] == '<' )
			{
				printf("minishell: parse error near '%c'\n", cmd[i]);
				return (-1);
			}
		}
		else if ((cmd[i] == '>' || cmd[i] == '<') && (cmd[skip_blank(cmd + i + 1) + i + 1] == '|' || cmd[skip_blank(cmd + i + 1) + i + 1] == '<' || cmd[i + 1] == '<' || cmd[i + 1] == '>' || cmd[skip_blank(cmd + i + 1) + i + 1] == '>' || !cmd[skip_blank(cmd + i + 1) + 1]))
		{
			printf("minishell: parse error near '%c'\n", cmd[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}
