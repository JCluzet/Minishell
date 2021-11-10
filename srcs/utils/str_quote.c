/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:48:53 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 18:50:12 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		duoquote(char *cmd, int v)
{
	int i;
	int s;
	int j;

	j = 0;
	s = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
			s++;
		if (cmd[i] == '\'')
			j++;
		if (i == v)
		{
			if (s % 2 == 0 && j % 2 == 0)
				return (0);
			else
				return(1);
		}
		i++;
	}
	return (0);
}

int		is_indquote(char *cmd, int v)
{
	int i;
	int s;

	s = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
			s++;
		if (i == v)
		{
			if (s % 2 == 0)
				return (1);
			else
				return(0);
		}
		i++;
	}
	return (0);
}

int		find_squotes(char *cmd, int i, char c)
{
	if (cmd[i] != '\"')
		return (i);
	else
		return(i+1);
	return (i+1);
}

int		is_insquote(char *cmd, int v)
{
	int i;
	int s;

	s = 0;
	i = 0;

	while(cmd[i])
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
			{
				if (i == v)
					return (1);
				i++;
			}
			if (i == v)
				return (1);
		}
		if(cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
			{
				if (i == v)
					return (0);
				i++;
			}
			if (i == v)
				return (0);
		}
		i++;
	}
	return (1);
}
