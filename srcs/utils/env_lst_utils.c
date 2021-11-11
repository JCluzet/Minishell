/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:29:26 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 15:39:33 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_lst	*remove_first_elem(t_env_lst *list)
{
	t_env_lst	*tmp;

	tmp = list->next;
	deallocate_env_lst_elem(list);
	return (tmp);
}

void	remove_last_elem(t_env_lst *list, t_env_lst *tmp)
{
	tmp->next = NULL;
	deallocate_env_lst_elem(list);
}

t_env_lst	*remove_elem(t_env_lst *list, char *arg)
{
	t_env_lst	*first;
	t_env_lst	*tmp;

	first = list;
	if (!ft_strncmp(list->name, arg, len(list->name))
		&& len(list->name) == lenequal(arg))
		return (remove_first_elem(list));
	while (list->next)
	{
		if (!ft_strncmp(list->name, arg, len(list->name))
			&& len(list->name) == lenequal(arg))
			break ;
		tmp = list;
		list = list->next;
	}
	if (!list->next)
		remove_last_elem(list, tmp);
	else
	{
		list = list->next;
		deallocate_env_lst_elem(tmp->next);
		tmp->next = list;
	}
	return (first);
}

t_env_lst	*add_elem(t_env_lst *list, char *arg)
{
	char		**line;
	t_env_lst	*new;

	line = split_env(arg, '=');
	new = allocate_env_lst_elem(line);
	new->next = list;
	return (new);
}

int	does_elem_exists(t_env_lst *list, char *arg)
{
	while (list)
	{
		if (!ft_strncmp(list->name, arg, len(list->name))
			&& len(list->name) == lenequal(arg))
			return (1);
		list = list->next;
	}
	return (0);
}
