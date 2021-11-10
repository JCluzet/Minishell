/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 17:40:25 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 17:50:54 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_env(t_sdata *sdata)
{
	int				i;
	t_env_lst		*list;

	i = 0;
	list = sdata->env_lst;
	while (list)
	{
		if (!list->var)
		{
			list = list->next;
			continue ;
		}
		write(1, list->name, len(list->name));
		write(1, "=", 1);
		write(1, list->var, len(list->var));
		write(1, "\n", 1);
		list = list->next;
	}
	sdata->lrval = 0;
}
