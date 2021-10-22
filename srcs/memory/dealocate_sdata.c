/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealocate_sdata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:58:36 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/22 13:34:17 by ambelkac         ###   ########.fr       */
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
	free(elem->name);
	free(elem->var);
	free(elem);
}

void	deallocate_sdata(t_sdata *sdata)
{
	t_cmd_lst *tmp;

	deallocate_cmd_list(sdata->cmds);
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
