/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 02:35:58 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/11 04:06:52 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_in_set(str[i], ENV_CHAR_LIST))
			return (i);
		i++;
	}
	return (i);
}

int	int_len(int i)
{
	int	count;

	count = 1;
	while (i > 9)
	{
		i = i / 10;
		count++;
	}
	return (count);
}
