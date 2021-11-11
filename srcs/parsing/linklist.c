/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:16:17 by jo                #+#    #+#             */
/*   Updated: 2021/11/11 23:51:34 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_lst	*init_linkedlist(void)
{
	t_cmd_lst	*cmds;

	cmds = malloc(sizeof(t_cmd_lst));
	if (!cmds)
		return (NULL);
	cmds->rdr = NULL;
	cmds->first_rdr = NULL;
	cmds->last_rdr = NULL;
	cmds->cmd = NULL;
	cmds->argv = NULL;
	cmds->cmd_path = NULL;
	cmds->type_last_rdr_out = 0;
	cmds->type_last_rdr_in = 0;
	cmds->fd_nbr = 0;
	cmds->fd_stack = NULL;
	cmds->last_fd_in = 0;
	cmds->save_stdin = 0;
	cmds->redir_ins = NULL;
	cmds->redir_outs = NULL;
	cmds->reddir_append = NULL;
	cmds->reddir_heredoc = NULL;
	cmds->next = NULL;
	return (cmds);
}

t_cmd_lst	*insertion_linklist(t_cmd_lst *cmds)
{
	t_cmd_lst	*new;

	new = malloc(sizeof(t_cmd_lst));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->argv = NULL;
	new->first_rdr = NULL;
	new->last_rdr = NULL;
	new->rdr = NULL;
	new->cmd_path = NULL;
	new->fd_nbr = 0;
	new->fd_stack = NULL;
	new->type_last_rdr_out = 0;
	new->type_last_rdr_in = 0;
	new->last_fd_in = 0;
	new->save_stdin = 0;
	new->next = NULL;
	new->redir_ins = NULL;
	new->redir_outs = NULL;
	new->reddir_append = NULL;
	new->reddir_heredoc = NULL;
	cmds->next = new;
	return (new);
}
