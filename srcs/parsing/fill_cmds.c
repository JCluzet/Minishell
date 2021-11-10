/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:58:41 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 22:47:17 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_cmds(t_sdata *data, t_cmd_lst *cmds, char *cmd)
{
	//printf("\ncmd 0>>|%s|\n", cmd);
	cmd = replace_dollars(cmd, data);  // NICKEL

	//printf("\ncmd 1>>|%s|\n", cmd);
	malloc_and_stock_redir(cmds, cmd); // NICKEL
	
	//printf("\ncmd 1>>|%s|\n", cmd);
	cmd = rmv_rdr_from_cmd(cmd); 
	//printf("\ncmd 2>>|%s|\n", cmd);
	
	cmds->argv = split_arg(cmd, ' ');
	if (cmds->argv[0])
		cmds->cmd = ft_strdup_free(cmds->argv[0], 0);
	cmds->cmd_path = NULL;
	cmds->builtin_idx = is_builtin(cmds->cmd);
}

int	end_first_rdr(char *cmd)
{
	int	i;
	int	tot;

	tot = 0;
	i = 0;
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if (cmd[i] == '<' && cmd[i + 1] == '<')
			i = find_lenght_file(cmd + i + 2) + i + 2;
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
			i = find_lenght_file(cmd + i + 2) + i + 2;
		else if (cmd[i] == '<')
			i = find_lenght_file(cmd + i + 1) + i + 1;
		else if (cmd[i] == '>')
			i = find_lenght_file(cmd + i + 1) + i + 1;
		else if (cmd[i] != ' ')
			return (i);
		if (cmd[i])
			i++;
	}
	return (0);
}

int	get_last_rdr_idx(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if (cmd[i] == '<' || cmd[i] == '>')
			return (i);
		i++;
	}
	return (i);
}

int	get_first_rdr_idx(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			if (is_cmd_after_file(cmd, i + 2))
				return (is_cmd_after_file(cmd, i + 2));
			i++;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
		{
			if (is_cmd_after_file(cmd, i + 2))
				return (is_cmd_after_file(cmd, i + 2));
			i++;
		}
		else if (cmd[i] == '<')
		{
			if (is_cmd_after_file(cmd, i + 1))
				return (is_cmd_after_file(cmd, i + 1));
		}
		else if (cmd[i] == '>')
		{
			if (is_cmd_after_file(cmd, i + 1))
				return (is_cmd_after_file(cmd, i + 1));
		}
		i++;
	}
	return (i);
}

int	is_cmd_after_file(char *cmd, int nb)
{
	int	i;

	i = skip_blank(cmd);
	while ((cmd[i] != ' ' && cmd[i] != '\t') && cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		i++;
	}
	i = skip_blank(cmd + i);
	if (cmd[i] && cmd[i] != '<' && cmd[i] != '>')
		return (nb + i);
	return (-1);
}