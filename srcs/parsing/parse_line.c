/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:08:47 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/30 02:42:56 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_lst	*parse_line(t_sdata *sdata, char *line)
{
	t_cmd_lst	*cmd;
	t_cmd_lst	*firstcmd;
	char		**mul_cmd;
	int			i;

	i = 0;
	cmd = init_linkedlist();
	firstcmd = cmd;
	line = line + cut_first_redir(line, cmd);
	mul_cmd = split_thepipe(line, '|');
	while (i < sdata->nb_of_cmds)
	{
		if (i != 0)
			cmd = insertion_linklist(cmd);
		fill_cmds(cmd, mul_cmd[i]);
		if (cmd->builtin_idx == -1)
			cmd->cmd_path = is_cmd_executable(cmd->cmd, sdata);
		i++;
	}
	printf_linked_list(firstcmd, sdata->nb_of_cmds);
	return (firstcmd);
}

int		cut_first_redir(char *line, t_cmd_lst *cmd)
{
	int i;

	i = skip_blank(line);
	cmd->first_rdr = initrdr2();
	if (line[i] == '<' && line[i + 1] == '<')
	{
		cmd->first_rdr->nb_redir_hdoc = 1;
		return (i + 2);
	}
	if (line[i] == '>' && line[i + 1] == '>')
	{
		cmd->first_rdr->nb_redir_app = 1;
		return (i + 2);
	}
	if (line[i] == '<')
	{
		cmd->first_rdr->nb_redir_out = 1;
		return (i + 1);
	}
	if (line[i] == '>')
	{
		cmd->first_rdr->nb_redir_in = 1;
		return (i + 1);
	}
	return(0);
}


int		pipe_check(char *str)
{
	int i;
	int blank;
	int cmd;

	cmd = 1;
	blank = -1;
	i = 0;
	while(str[i])
	{
		i = find_quotes(str, i, str[i]);
		if (str[i] == '|')
		{
			cmd++;
			if (i == len(str) - 1)
				return (-1);
			if (i == 0)
				return (-1);
			if (blank == -1)
				return (-1);
			blank = -1;
		}
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '|')
			blank = 0;
		i++;
	}
	if (blank != -1)
		return(cmd);
	return(blank);
}

int		quotes_check(char *str)
{
	t_quote qt;
	qt.double_q = 0;
	qt.simple_q = 0;
	int i;

	i = 0;
	while (str[i])
	{
		checkquotes(str[i], &qt);
		i++;
	}
	if (qt.simple_q % 2 != 0)
	{
		printf("minishell: unexpected EOF while looking for matching '\''\n");
		return(-1);
	}
	if (qt.double_q % 2 != 0)
	{
		printf("minishell: unexpected EOF while looking for matching '\"'\n");
		return(-1);
	}
	return(0);
}	

int		checkquotes(char c, t_quote *qt)
{
	if (c == '\"')
	{
		if (qt->simple_q % 2 == 0)
			qt->double_q++;
		else
			qt->double_q_insimple++;
	}
	if (c == '\'')
	{
		if (qt->double_q % 2 == 0)	
			qt->simple_q++;
		else
			qt->simple_q_indouble++;
	}
	return(0);
}

int		check_error(t_cmd_lst *cmds)
{
	if (!cmds)
		return(-1);
	if (((((cmds->builtin_idx > 6) && !cmds->cmd_path) || (cmds->builtin_idx == -1 && !cmds->cmd_path)) && cmds->argv))
	{
		write(1, "minishell: command not found: ", 31);
		write(1, cmds->cmd, len(cmds->cmd));
		write(1, "\n", 1);
	}
	return(0);
}
