/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealocate_sdata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:58:36 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 18:56:07 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	free(elem);
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

int	deallocate_env_lst(t_env_lst *list)
{
	t_env_lst	*tmp;

	if (!list)
		return (1);
	tmp = list;
	while (list->next)
	{
		list = list->next;
		deallocate_env_lst_elem(tmp);
		tmp = list;
	}
	deallocate_env_lst_elem(list);
	return (1);
}

void	deallocate_sdata(t_sdata *sdata)
{
	deallocate_cmd_list(sdata->f_cmds);
	free_arr(sdata->env);
	free_arr(sdata->bin_paths);
	deallocate_env_lst(sdata->env_lst);
	close(sdata->save_stdin);
	close(sdata->save_stdout);
}
