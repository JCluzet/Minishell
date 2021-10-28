/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealocate_sdata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:58:36 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/28 15:24:21 by ambelkac         ###   ########.fr       */
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

void	deallocate_cmd_list(t_cmd_lst *cmd)
{
	t_cmd_lst	*tmp;
	
	while (cmd)
	{
		free(cmd->cmd);
		free_arr(cmd->argv);
		free(cmd->cmd_path);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	deallocate_env_lst_elem(t_env_lst *elem)
{
	if (!elem)
		return ;
	free(elem->name);
	free(elem->var);
	free(elem);
}

void	deallocate_env_lst(t_env_lst *list)
{
	t_env_lst *tmp;

	tmp = list;
	while (list->next)
	{
		list = list->next;
		deallocate_env_lst_elem(tmp);
		tmp = list;
	}
	deallocate_env_lst_elem(list);
}

void	deallocate_sdata(t_sdata *sdata)
{
	t_cmd_lst *tmp;

//	deallocate_cmd_list(sdata->cmds);
	free_arr(sdata->env);
	free_arr(sdata->bin_paths);
	deallocate_env_lst(sdata->env_lst);
	free(sdata);
}
