#include "../../includes/minishell.h"

static int	count_words(const char *str, char c)
{
	int i;
	int trigger;
	int s_quotes;
	int d_quotes;

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
			if (is_double_redir(*str, *str+1))
				str++;
		}
		str++;
	}
	return (i);
}

int is_double_redir(char c, char c1)
{
	if ((c == '<' && c1 == '<') || (c == '>' && c1 == '>'))
		return (1);
	return(0);
}

int issep(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return(0);
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

char		**split_thepipe(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;
	int		s_quotes;
	int		d_quotes;

	s_quotes = 0;
	d_quotes = 0;
	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= len(s))
	{
		if (s[i] == '\'')
			s_quotes++;
		if (s[i] == '\"')
			d_quotes++;
		if (s[i] != c && index < 0)
			index = i;
		else if (((issep(s[i]) && (s_quotes % 2 == 0 && d_quotes % 2 == 0)) || i == len(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}