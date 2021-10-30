/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:16:17 by jo                #+#    #+#             */
/*   Updated: 2021/10/30 20:16:29 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

// malloc and init linked list for cmds and return it

t_cmd_lst	*init_linkedlist(void)
{
	t_cmd_lst *cmds;
	
	cmds = malloc(sizeof(t_cmd_lst));
	cmds->cmd = NULL;
	cmds->argv = NULL;
	cmds->cmd_path = NULL;
	cmds->next = NULL;
	return(cmds);
}

// insert a new node in the linked list and return it

t_cmd_lst	*insertion_linklist(t_cmd_lst *cmds)
{
	t_cmd_lst *new;
	
	new = malloc(sizeof(t_cmd_lst));
	new->cmd = NULL;
	new->argv = NULL;
	new->cmd_path = NULL;
	new->next = NULL;
	cmds->next = new;
	return(new);
}

// print linked list
void			printf_linked_list(t_cmd_lst *cmd, int nb)
{
	int i;

	i = 0;
	if (cmd->first_rdr->nb_redir_app == 1)
		printf("\nFIRST REDIR \">>\" DETECTED\n\n");
	if (cmd->first_rdr->nb_redir_hdoc == 1)
		printf("\nFIRST REDIR \"<<\" DETECTED\n\n");
	if (cmd->first_rdr->nb_redir_out == 1)
		printf("\nFIRST REDIR \"<\" DETECTED\n\n");
	if (cmd->first_rdr->nb_redir_in == 1)
		printf("\nFIRST REDIR \">\" DETECTED\n\n");
	while (cmd->next != NULL) 
	{
		if (cmd->argv)
			print_cmds(cmd, cmd->argv[0], 0, i);
		else
			print_cmds(cmd, cmd->argv[0], 1, i);
		cmd = cmd->next;
		i++;
	}
	if (cmd->argv)
		print_cmds(cmd, cmd->argv[0], 0, i);
	else
		print_cmds(cmd, cmd->argv[0], 1, i);
}

void	print_cmds(t_cmd_lst *cmds, char *cmd, int v, int i)
{
	int u;
	i++;

	u = 1;
	//printf("nb of cmd = %d\n\n", nb_of_cmds(cmd));
	printf("\n-- COMMAND %d DETECTED --\n", i);
	if (v == 0)
		printf("cmd > %s\n", cmds->cmd);
	else 
		printf("cmd > (null)\n");
	while (v == 0 && cmds->argv[u] != NULL)
	{
		printf("argv %d > %s\n", u, cmds->argv[u]);
		u++;
	}
	if (v == 0 && cmds->argv[1] == NULL)
		printf("argv > (null)\n");
	i = -1;
	while (cmds->redir_ins[i++])
		printf("%d redir_in = %s\n",i+1 , cmds->redir_ins[i]);
	i = -1;
	while (cmds->redir_outs[i++])
		printf("%d redir_out = %s\n",i+1 , cmds->redir_outs[i]);
	i = -1;
	while (cmds->reddir_append[i++])
		printf("%d redir_append = %s\n",i+1 , cmds->reddir_append[i]);
	i = -1;
	while (cmds->reddir_heredoc[i++])
		printf("%d redir_heredoc = %s\n",i +1, cmds->reddir_heredoc[i]);



	if (cmds->last_rdr->nb_redir_in != 0)
		printf("last_rdr_in detected and is the %d redir\n", cmds->rdr->nb_redir_in);
	if (cmds->last_rdr->nb_redir_out != 0)
		printf("last_rdr_out detected and is the %d redir\n", cmds->rdr->nb_redir_out);
	if (cmds->last_rdr->nb_redir_app != 0)
		printf("last_rdr_append detected and is the %d redir\n", cmds->rdr->nb_redir_app);
	if (cmds->last_rdr->nb_redir_hdoc != 0)
		printf("last_rdr_heredoc detected and is the %d redir\n", cmds->rdr->nb_redir_hdoc);
	
	printf("builtin_idx > %d\n", cmds->builtin_idx);
	printf("\n");
}