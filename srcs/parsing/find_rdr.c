/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rdr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:25:28 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/11 17:33:54 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_size_rdr2(t_cmd_lst *cmds, char *cmd, int i)
{
	if (cmd[i] == '<' && cmd[i + 1] == '<')
	{
		cmds->type_last_rdr_in = 2;
		cmds->rdr->nb_redir_hdoc++;
		i++;
	}
	else if (cmd[i] == '>' && cmd[i + 1] == '>')
	{
		cmds->type_last_rdr_out = 2;
		cmds->rdr->nb_redir_app++;
		i++;
	}
	else if (cmd[i] == '<')
	{
		cmds->rdr->nb_redir_out++;
		cmds->type_last_rdr_in = 1;
	}
	return (i);
}

void	get_size_redir(t_cmd_lst *cmds, char *cmd)
{
	int	i;
	int	j;

	cmds->rdr = initrdr2();
	cmds->type_last_rdr_in = 0;
	cmds->type_last_rdr_out = 0;
	i = 0;
	while (cmd[i])
	{
		j = i;
		i = get_size_rdr2(cmds, cmd, i);
		if (cmd[i] == '>' && j == i)
		{
			cmds->rdr->nb_redir_in++;
			cmds->type_last_rdr_out = 1;
		}
		else if (j == i)
			i = find_quotes(cmd, i, cmd[i]);
		i++;
	}
}
