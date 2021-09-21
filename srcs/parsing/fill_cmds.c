/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:58:41 by ambelkac          #+#    #+#             */
/*   Updated: 2021/09/21 21:08:36 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_lst	*fill_multi_cmds(char *cmd)
{
	t_cmd_lst *cmds;
	char **mul_cmd;
	int i;
	
	mul_cmd = str_to_word_arr(cmd, '|');          // separe la ligne cmd en plusieurs commandes avec ; MAIS aussi si il ya des quotes genre echo ";" :/
	i = 0;
	cmds = malloc(sizeof(t_cmd_lst) * nb_of_cmds(cmd));
	while (i < nb_of_cmds(cmd))
	{
		fill_cmds(&cmds[i], mul_cmd[i]);
		i++;
	}
	return(cmds);
}

void	fill_cmds(t_cmd_lst *cmds, char *cmd)
{
	cmds->argv = str_to_word_arr(cmd, ' ');       // store l arg apres l'espace
	if (cmds->argv)
		cmds->cmd = ft_strdup_free(cmds->argv[0], 0); // store la cmd
	cmds->cmd_path = NULL;
	if (cmds->argv)
	{
		cmds->builtin_idx = is_builtin(cmds->argv[0]); 
		print_cmds(cmds, cmd, 0);// changer pour stock
	}
	else
	{
		cmds->builtin_idx = -1;
		print_cmds(cmds, cmd, 1);
	}
	cmds->reff_arg = NULL;
	// Place holder
}

void	print_cmds(t_cmd_lst *cmds, char *cmd, int v)
{
	int u;

	u = 1;
	//printf("nb of cmd = %d\n\n", nb_of_cmds(cmd));
	printf("\n-- COMMAND DETECTED --\n");
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
