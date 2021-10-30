/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:58:41 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/30 02:44:10 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_cmds(t_cmd_lst *cmds, char *cmd)
{
	malloc_and_stock_redir(cmds, cmd);
	cmd = rmv_rdr_from_cmd(cmd);
	cmds->argv = split_thespace(cmd, ' ');
	if (cmds->argv)
		cmds->cmd = ft_strdup_free(cmds->argv[0], 0);
	cmds->cmd_path = NULL;
	if (cmds->argv)
		cmds->builtin_idx = is_builtin(cmds->argv[0]);
	else
		cmds->builtin_idx = -1;
}

// a function that return the index of the string coresponding to the last redir before the cmd

char	*rmv_rdr_from_cmd(char *cmd)
{
	//printf("la cmd commence a l'index %d\n", get_last_rdr_idx(cmd));       // manque suppresion des redir avant la cmd (comme la premiere redir)
	return (ft_substr(cmd, 0, get_last_rdr_idx(cmd)));                      // supprime les redir se trouvant apres la cmd
}

int		get_last_rdr_idx(char *cmd)
{
	int i;

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

int		get_first_rdr_idx(char *cmd)
{
	int i;

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

int		is_cmd_after_file(char *cmd, int nb)
{
	int i;

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