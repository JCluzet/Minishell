/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rdr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo <jo@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:25:28 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/13 15:44:06 by jo               ###   ########.fr       */
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
		cmds->rdr->nro++;
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
			cmds->rdr->nri++;
			cmds->type_last_rdr_out = 1;
		}
		else if (j == i)
			i = find_quotes(cmd, i, cmd[i]);
		i++;
	}
}

int	find_lenghtwq(char *cmd)
{
	int	i;
	int	size;
	int	temp;

	size = 0;
	i = skip_blank(cmd);
	while (cmd[i])
	{
		temp = i;
		i = skip_quotes_arg(cmd, i);
		if (temp == i && (cmd[i] == ' ' || cmd[i] == '\t'
				|| cmd[i] == '<' || cmd[i] == '>'))
			return (i);
		else if (temp == i)
			i++;
	}
	return (i);
}
