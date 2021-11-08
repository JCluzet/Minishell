/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealocate_sdata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:58:36 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/08 21:01:00 by amine            ###   ########.fr       */
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

void	deallocate_cmd_elem(t_cmd_lst *elem)
{
	free(elem->cmd);
	free_arr(elem->argv);
	free(elem->cmd_path);
	free(elem->rdr);
	free_arr(elem->reddir_append);
	free_arr(elem->reddir_heredoc);
	free_arr(elem->redir_ins);
	free_arr(elem->redir_outs);
	free(elem->last_rdr);
	free(elem->first_rdr);
	clear_fd_stack(elem);
}

void	deallocate_cmd_list(t_cmd_lst *cmds)
{
	t_cmd_lst	*tmp;

	if (!cmds)
		return ;
	while (cmds->next)
	{
		tmp = cmds;
		cmds = cmds->next;
		deallocate_cmd_elem(tmp);
	}
	deallocate_cmd_elem(cmds);
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

	deallocate_cmd_list(sdata->cmds);
	free_arr(sdata->env);
	free_arr(sdata->bin_paths);
	deallocate_env_lst(sdata->env_lst);
	close(sdata->save_stdin);
	close(sdata->save_stdout);
}
