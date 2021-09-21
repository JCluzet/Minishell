/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 17:39:17 by ambelkac          #+#    #+#             */
/*   Updated: 2021/08/12 18:39:49 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shell_exit(t_sdata *sdata)
{
	if (sdata->cmds->argv == NULL || tablen(sdata->cmds->argv) == 1)
	{
		printf("exit\n");
		exit(0);
	}
	if (!is_number(sdata->cmds->argv[1], 0))
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", sdata->cmds->argv[0]);
		exit(255);
	}
	if (is_number(sdata->cmds->argv[1], 0))
	{
		if (tablen(sdata->cmds->argv) == 2)
			exit(ft_atoi(sdata->cmds->argv[0]));
		else
		{
			printf("exit\nexit: too many arguments\n");
			sdata->lrval = 1;
		}
	}
}

int 	usage_exit(char **argv)
{
	if (!argv)
	{
		printf("exit\n");
		exit(0);
	}
	if (!is_number(argv[1], 0))
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", argv[0]);
		exit(255);
	}
	if (is_number(argv[1], 0))
	{
		if (tablen(argv) == 1)
			exit(ft_atoi(argv[0]));
		else
		{
			printf("exit\nexit: too many arguments\n");
			return (1);
		}
	}
	return (1);
}
