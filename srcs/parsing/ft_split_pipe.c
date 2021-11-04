/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 00:30:11 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/05 00:30:16 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words(const char *str, char c)
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
		if (!issep(*str) && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (issep(*str) && (s_quotes % 2 == 0 && d_quotes % 2 == 0))
		{
			trigger = 0;
		}
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