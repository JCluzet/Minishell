/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:29:46 by ambelkac          #+#    #+#             */
/*   Updated: 2021/08/20 04:52:11 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// write tout les arguments de la cmd >>  pas seulement le 1

void	echo(t_sdata *sdata)
{
	sdata->lrval = 0;
	if (tablen(sdata->cmds->argv) == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	if (!ft_strncmp(sdata->cmds->argv[1], "$?", 2) && len(sdata->cmds->argv[1]) == 2)
	{
		printf("%d\n", sdata->lrval);
		return ;
	}
	if (!ft_strncmp(sdata->cmds->argv[1], "-n", 2) && len(sdata->cmds->argv[1]) == 2)
	{
		if (tablen(sdata->cmds->argv) == 2)
			return ;
		write(1, sdata->cmds->argv[2], len(sdata->cmds->argv[2]));
		return ;
	}
	else
		write(1, sdata->cmds->argv[1], len(sdata->cmds->argv[1]));
	write(1, "\n", 1);
}
