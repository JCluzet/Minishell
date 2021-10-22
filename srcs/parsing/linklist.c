/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 01:16:17 by jo                #+#    #+#             */
/*   Updated: 2021/10/22 12:51:11 by ambelkac         ###   ########.fr       */
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
	cmds->reff_arg = NULL;
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
	new->reff_arg = NULL;
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
	while (cmd->next != NULL) 
	{
		printf("%s", cmd->argv[0]);
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
	printf("builtin_idx > %d\n", cmds->builtin_idx);
	printf("\n");
}