/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:16:17 by jo                #+#    #+#             */
/*   Updated: 2021/11/11 22:48:02 by jcluzet          ###   ########.fr       */
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

/*
** 2 functions to print parsing
*/

/*
** void	printf_linked_list(t_cmd_lst *cmd)
** {
** 	int	i;
** 
** 	i = 0;
** 	while (cmd->next != NULL)
** 	{
** 		if (cmd->argv)
** 			print_cmds(cmd, 0, i);
** 		else
** 			print_cmds(cmd, 1, i);
** 		cmd = cmd->next;
** 		i++;
** 	}
** 	if (cmd->argv)
** 		print_cmds(cmd, 0, i);
** 	else
** 		print_cmds(cmd, 1, i);
** }
** 
** void	print_cmds(t_cmd_lst *cmds, int v, int i)
** {
** 	int	u;
** 
** 	i++;
** 	u = 1;
** 	printf("\n-- COMMAND %d DETECTED --\n", i);
** 	if (v == 0)
** 		printf("cmd > %s\n", cmds->cmd);
** 	else
** 		printf("cmd > (null)\n");
** 	while (cmds->argv[0] && v == 0 && cmds->argv[u] != NULL)
** 	{
** 		printf("argv %d > %s\n", u, cmds->argv[u]);
** 		u++;
** 	}
** 	printf("builtin_idx > %d\n", cmds->builtin_idx);
** 	if (cmds->argv[0] && v == 0 && cmds->argv[1] == NULL)
** 		printf("argv > (null)\n\n");
** 	i = -1;
** 	while (cmds->redir_ins[++i])
** 		printf("redir_in %d = %s\n", i + 1, cmds->redir_ins[i]);
** 	i = -1;
** 	while (cmds->redir_outs[++i])
** 		printf("redir_out %d = %s\n", i + 1, cmds->redir_outs[i]);
** 	i = -1;
** 	while (cmds->reddir_append[++i])
** 		printf("redir_append %d = %s\n", i + 1, cmds->reddir_append[i]);
** 	i = -1;
** 	while (cmds->reddir_heredoc[++i])
** 		printf("redir_heredoc %d = %s\n", i + 1, cmds->reddir_heredoc[i]);
** 	printf("\n");
** 	if (cmds->type_last_rdr_in != 0)
** 		printf("last_rdr_in detected = %d   << 2=double & 1=simple\n",
** 			cmds->type_last_rdr_in);
** 	if (cmds->type_last_rdr_out != 0)
** 		printf("last_rdr_out detected = %d   << 2=double & 1=simple\n",
** 			cmds->type_last_rdr_out);
** 	printf("\n");
** }
*/
