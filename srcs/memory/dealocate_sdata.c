/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealocate_sdata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:58:36 by ambelkac          #+#    #+#             */
/*   Updated: 2021/09/20 23:40:26 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_arr(char **arr)
{
	int		i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}

void	deallocate_cmd_elem(t_cmd_lst *cmd)
{
	if (!cmd || !cmd->argv)
		return ;
	free(cmd->cmd);
	free_arr(cmd->argv);
	free(cmd->cmd_path);
	free(cmd->reff_arg);
	free(cmd);
}

void	deallocate_env_lst_elem(t_env_lst *elem)
{
	free(elem->name);
	free(elem->var);
	free(elem);
}

void	deallocate_sdata(t_sdata *sdata)
{
	t_cmd_lst *tmp;

	deallocate_cmd_elem(sdata->cmds);
	// FREE CMD LIST
	// tmp = sdata->cmds;
	// while (sdata->cmds)
	// {
	// 	if (sdata->cmds)
	// 		tmp = sdata->cmds->next;
	// 	sdata->cmds = tmp;
	// }
	free_arr(sdata->env);
	free_arr(sdata->bin_paths);
}
