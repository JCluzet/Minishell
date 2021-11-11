/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:48:53 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 16:13:47 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	duoquote(char *cmd, int v)
{
	int	i;
	int	s;
	int	j;

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
				return (1);
		}
		i++;
	}
	return (0);
}

int	skip_i_qu(char *cmd, int i, int v)
{
	if (cmd[i] == '\"')
	{
		i++;
		while (cmd[i++] != '\"')
			if (i == v)
				return (-1);
		if (i == v)
			return (-1);
	}
	if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i++] != '\'')
			if (i == v)
				return (-2);
		if (i == v)
			return (-2);
	}
	return (i);
}

int	is_insquote(char *cmd, int v)
{
	int	i;
	int	s;

	s = 0;
	i = 0;
	while (cmd[i])
	{
		i = skip_i_qu(cmd, i, v);
		if (i == -1)
			return (1);
		if (i == -2)
			return (0);
		i++;
	}
	return (1);
}

int	skip_quotes_arg(char *cmd, int i)
{
	if (cmd[i] == '\"')
	{
		i++;
		while (cmd[i] != '\"' && cmd[i])
			i++;
		if (cmd[i])
			i++;
	}
	else if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] != '\'' && cmd[i])
			i++;
		if (cmd[i])
			i++;
	}
	return (i);
}

char	**skip_quotes_split(const char *s, int i, char **split, int j)
{
	int		qt[2];
	int		index;

	index = -1;
	qt[0] = 0;
	qt[1] = 0;
	while (i <= len(s))
	{
		if (s[i] == '\'')
			qt[0]++;
		if (s[i] == '\"')
			qt[1]++;
		if (s[i] != '|' && index < 0)
			index = i;
		else if (((s[i] == '|' && (qt[0] % 2 == 0 && qt[1] % 2 == 0))
				|| i == len(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
