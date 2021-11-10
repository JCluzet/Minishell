/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_sdata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:36:18 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 15:51:38 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_lst	*allocate_cmd_elem(void)
{
	t_cmd_lst	*cmd;

	cmd = malloc(sizeof(t_cmd_lst));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->argv = NULL;
	cmd->cmd_path = NULL;
	cmd->fd_stack = NULL;
	cmd->fd_nbr = 0;
	return (cmd);
}

t_env_lst	*allocate_env_lst_elem(char **line)
{
	t_env_lst	*elem;

	elem = malloc(sizeof(t_env_lst));
	if (!elem)
		return (NULL);
	for (int i = 0; line[i]; ++i)
		printf("Line[%d] : %s\n", i, line[i]);
	printf("\n");
	elem->name = line[0];
	elem->var = line[1];
	elem->next = NULL;
	free(line);
	return (elem);
}

int	allocate_env_lst(t_sdata *sdata, char **env)
{
	t_env_lst	*elem;
	t_env_lst	*next;
	char		**line;
	int			i;

	i = 1;
	if (!env || !env[0])
		return (EXIT_FAILURE);
	sdata->env_lst = allocate_env_lst_elem(split_env(env[0], '='));
	elem = sdata->env_lst;
	while (env[i])
	{
		next = allocate_env_lst_elem(split_env(env[i], '='));
		elem->next = next;
		elem = next;
		++i;
	}
	elem->next = NULL;
	return (EXIT_SUCCESS);
}


void	allocate_sdata(t_sdata *sdata, char **env)
{
	sdata->cmds = NULL;
	sdata->lrval = 0;
	sdata->env = dup_arr(env);
	if (allocate_env_lst(sdata, sdata->env) == EXIT_FAILURE)
	{
		sdata->env_lst = NULL;
		return ;
	}
	sdata->lrval = 0;
	sdata->save_stdin = dup(0);
	sdata->save_stdout = dup(1);
	sdata->bin_paths = str_to_word_arr(get_var_in_env(env, "PATH=") + 5, ':');
}
