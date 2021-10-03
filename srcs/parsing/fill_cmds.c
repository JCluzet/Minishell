/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo <jo@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:58:41 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/03 02:26:08 by jo               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_lst	*split_cmds(char *cmd)
{
	t_cmd_lst *cmds;
	t_cmd_lst *firstcmds;
	char **mul_cmd;
	int i;
	
	cmds = init_linkedlist();
	firstcmds = cmds;
	mul_cmd = split_thepipe(cmd, '|');
	//mul_cmd = str_to_word_arr(cmd, '|');          // separe la ligne cmd en plusieurs commandes avec ; MAIS aussi si il ya des quotes genre echo ";" :/
	i = 0;
	//cmds = malloc(sizeof(t_cmd_lst) * nb_of_cmds(cmd));
	while (i < nb_of_cmds(cmd))
	{
		if (i != 0)
		{
			cmds = insertion_linklist(cmds);
		}
		fill_cmds(cmds, mul_cmd[i]);
		i++;
	}
	return(firstcmds);
}


void	fill_cmds(t_cmd_lst *cmds, char *cmd)
{
	cmds->argv = split_thepipe(cmd, ' ');       // store l arg apres l'espace
	if (cmds->argv)
		cmds->cmd = ft_strdup_free(cmds->argv[0], 0); // store la cmd
	cmds->cmd_path = NULL;
	if (cmds->argv)
		cmds->builtin_idx = is_builtin(cmds->argv[0]); 
	else
		cmds->builtin_idx = -1;
	cmds->reff_arg = NULL;
}

void	print_cmds(t_cmd_lst *cmds, char *cmd, int v, int i)
{
	int u;
	i++;

	u = 1;
	//printf("nb of cmd = %d\n\n", nb_of_cmds(cmd));
	printf("-- COMMAND %d DETECTED --\n", i);
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
	printf("builtin_idx > %d\n\n", cmds->builtin_idx);
}

int		nb_of_cmds(char *cmd)
{
	int i;
	int u;

	u = 1;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			i = find_quotes(cmd, i, cmd[i]);
		if (cmd[i] == '|')
			u++;
		i++;
	}
	return(u);
}

int		find_quotes(char *cmd, int i, char c)
{
	i++;
	while (cmd[i] != c)
		i++;
	return(i);
}
