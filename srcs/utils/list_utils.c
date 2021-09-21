/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:55:59 by ambelkac          #+#    #+#             */
/*   Updated: 2021/08/20 05:00:42 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	listlen(t_env_lst *list)
{
	int		i;

	i = 0;
	while (list)
	{
		list = list->next;
		++i;
	}
	return (i);
}

int	lenequal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		++i;
	}
	return (i);
}

char	**list_to_arr(t_env_lst *list)
{
	char	**arr;

	arr = NULL;
	while (list)
	{
		arr = cncat_arr(arr, cncat(cncat(list->name, "=", 0, 0), list->var, 0, 0));
		list = list->next;
	}
	return (arr);
}

t_env_lst	*remove_first_elem(t_env_lst *list, char *arg)
{
	t_env_lst *tmp;

	tmp = list->next;
	deallocate_env_lst_elem(list);
	return (tmp);
}

void	remove_last_elem(t_env_lst *list, char *arg)
{
	t_env_lst	*tmp;

	tmp = list->next;
	list->next = NULL;
	deallocate_env_lst_elem(tmp);
}

t_env_lst	*remove_elem(t_env_lst *list, char *arg)
{
	t_env_lst	*first;
	t_env_lst	*tmp;

	first = list;
	if (!ft_strncmp(list->name, arg, len(list->name)) && len(list->name) == lenequal(arg))
		return (remove_first_elem(list, arg));
	while (list->next)
	{
		if (!ft_strncmp(list->name, arg, len(list->name)) && len(list->name) == lenequal(arg))
			break ;
		tmp = list;
		list = list->next;
	}
	if (!list->next)
		remove_last_elem(list, arg);
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
	char	**line;
	t_env_lst	*new;

	line = str_to_word_arr(arg, '=');
	new = allocate_env_lst_elem(line);
	new->next = list;
	return (new);
}

int		does_elem_exists(t_env_lst *list, char *arg)
{
	while (list)
	{
		if (!ft_strncmp(list->name, arg, len(list->name)) && len(list->name) == lenequal(arg))
			return (1);
		list = list->next;
	}
	return (0);
}