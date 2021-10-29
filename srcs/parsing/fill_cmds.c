/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:58:41 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/29 19:55:47 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_cmds(t_cmd_lst *cmds, char *cmd)
{
	malloc_and_stock_redir(cmds, cmd);
	// rmv_rdr_from_cmd(cmds, cmd); supprimer la premiere partie des redir et la derniere 
	cmds->argv = split_thespace(cmd, ' ');
	if (cmds->argv)
		cmds->cmd = ft_strdup_free(cmds->argv[0], 0);
	cmds->cmd_path = NULL;
	if (cmds->argv)
		cmds->builtin_idx = is_builtin(cmds->argv[0]);
	else
		cmds->builtin_idx = -1;
}