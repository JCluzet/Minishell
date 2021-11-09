/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:09:52 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/09 15:54:37 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		error_print_free(int rval, char *str, t_sdata *sdata)
{
	if (str)
		putstr_err(str);
	if (sdata)
		deallocate_sdata(sdata);
	return (rval);
}