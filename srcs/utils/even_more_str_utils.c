/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_str_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:03:57 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 16:42:53 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_x(char const *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

char	*get_file_redir(char *cmd, char *file)
{
	t_skquo	skqu;
	int		j;

	skqu.size = 0;
	skqu.i = 0;
	skqu.i = skip_blank(cmd);
	while (cmd[skqu.i])
	{
		j = skqu.i;
		skqu = skip_qu_file(skqu, cmd, file);
		if ((cmd[skqu.i] == ' ' || cmd[skqu.i] == '\t'
				|| cmd[skqu.i] == '<' || cmd[skqu.i] == '>') && skqu.i == j)
		{
			file[skqu.size] = '\0';
			return (file);
		}
		else if (j == skqu.i)
			file[skqu.size++] = cmd[skqu.i++];
	}
	file[skqu.size] = '\0';
	if (skqu.size == 0)
		file = NULL;
	return (file);
}

t_skquo	skip_qu_file(t_skquo skqu, char *cmd, char *file)
{
	if (cmd[skqu.i] == '\"')
	{
		skqu.i++;
		while (cmd[skqu.i] != '\"' && cmd[skqu.i])
		{
			file[skqu.size] = cmd[skqu.i];
			skqu.size++;
			skqu.i++;
		}
		if (cmd[skqu.i])
			skqu.i++;
	}
	else if (cmd[skqu.i] == '\'')
	{
		skqu.i++;
		while (cmd[skqu.i] != '\'' && cmd[skqu.i])
		{
			file[skqu.size] = cmd[skqu.i];
			skqu.size++;
			skqu.i++;
		}
		if (cmd[skqu.i])
			skqu.i++;
	}
	return (skqu);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}
