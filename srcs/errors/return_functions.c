/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:09:52 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/08 20:41:19 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		error_print_free(int rval, char *str, t_sdata *sdata)
{
	if (str)
		fprintf(stderr, "%s\n", str);
	deallocate_sdata(sdata);
	return (rval);
}