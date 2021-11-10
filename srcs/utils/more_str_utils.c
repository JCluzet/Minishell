/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_str_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:03:14 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 18:32:20 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_x(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = '\0';
		++i;
	}
	return (str);
}

int	empty_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

int	issep(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	isspace_behind(char *str, int i)
{
	int	u;

	u = 0;
	if (i == 0)
		return (0);
	i--;
	while (i != 0)
	{
		if (str[i] != ' ' && str[i] != '\t')
			u = -1;
		i--;
	}
	return (u);
}

int	skip_blank(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		i++;
	return (i);
}
