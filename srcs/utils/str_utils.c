/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:44:56 by ambelkac          #+#    #+#             */
/*   Updated: 2021/09/22 00:22:39 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tablen(char **tab)
{
	int				i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		++i;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_number(char const *str, int i)
{
	int		count;

	count = 1;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[++i]))
		++count;
	return (count);
}

int	is_in_set(char c, char const *set)
{
	int		i;

	i = 0;
	if (!set[i])
		return (0);
	while (set[i])
	{
		if (c == set[i])
			return (1);
		++i;
	}
	return (0);
}

size_t	len(const char *str)
{
	int				i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int		len_x(char const *str, char c)
{
	int				i;
	
	i = 0;
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

char 	*str_x(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == ' ')
			str[i] = '\0';
		++i;
	}
	return (str);
}

int empty_str(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		++i;
	}
	return (1);
}
