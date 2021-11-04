/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 00:16:03 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/05 00:29:37 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words_space(const char *str, char c)
{
	int	i;
	int	trigger;
	int	s_quotes;
	int	d_quotes;

	s_quotes = 0;
	d_quotes = 0;
	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str == '\'')
			s_quotes++;
		if (*str == '\"')
			d_quotes++;
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c && (s_quotes % 2 == 0 && d_quotes % 2 == 0))
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char		**split_thespace(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;
	int		qt[2];

	qt[0] = 0;
	qt[1] = 0;
	if (!s)
		return (0);
	split = malloc((count_words_space(s, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= len(s))
	{
		if (s[i] == '\'')
			qt[0]++;
		if (s[i] == '\"')
			qt[1]++;
		if (s[i] != c && index < 0)
			index = i;
		else if (((s[i] == c && (qt[0] % 2 == 0 && qt[1] % 2 == 0))
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