/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:29:25 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 17:51:02 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_sdata *sdata)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		sdata->lrval = 1;
		return ;
	}
	write(1, path, len(path));
	write(1, "\n", 1);
	sdata->lrval = 0;
}
