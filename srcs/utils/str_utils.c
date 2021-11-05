/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:44:56 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/05 20:29:19 by jcluzet          ###   ########.fr       */
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

int issep(char c)
{
	if (c == '|')
		return (1);
	return(0);
}

int	isspace_behind(char *str, int i)
{
	int u;

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
	return(u);
}

int		skip_blank(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		i++;
	return(i);
}

char*	get_file_redir(char *cmd, char *file)
{
	int i;
	int size;

	size = 0;
	i = 0;
	i = skip_blank(cmd);
	while ((cmd[i+size] != ' ' && cmd[i+size] != '\t' && cmd[i+size] != '<' && cmd[i+size] != '>') && cmd[i+size])
	{
		file[size] = cmd[size + i];
		size++;
	}
	file[size] = '\0';
	if (size == 0)
		file = NULL;
	return (file);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char*)malloc(sizeof(*s) * (len + 1));
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