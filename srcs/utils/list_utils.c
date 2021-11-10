/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:55:59 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 18:30:24 by ambelkac         ###   ########.fr       */
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
		arr = cncat_arr(arr, cncat(
					cncat(list->name, "=", 0, 0), list->var, 0, 0));
		list = list->next;
	}
	return (arr);
}
