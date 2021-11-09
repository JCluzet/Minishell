/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:48:50 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/09 15:26:46 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strncpy(char *dest, char *src, int n)
{
	int				i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!dest)
		return (src);
	if (!src || !nb)
		return (dest);
	while (dest[i])
		++i;
	while (src[j] && nb)
	{
		dest[i] = src[j];
		i++;
		j++;
		--nb;
	}
	dest[i] = '\0';
	return (dest);
}

char	*cncat(char *str1, char *str2, int ifree1, int ifree2)
{
	char		*str3;
	size_t		i;

	if (!str1 && !str2)
		return (NULL);
	if (!str1)
		return (ft_strdup_free(str2, ifree2));
	if (!str2)
		return (ft_strdup_free(str1, ifree1));
	str3 = malloc(sizeof(char) * (len(str1) + len(str2) + 1));
	if (!str3)
		return (NULL);
	i = -1;
	while (++i < (size_t)(len(str1) + len(str2) + 1))
		str3[i] = '\0';
	str3 = ft_strncat(ft_strncat(str3, str1, len(str1)), str2, len(str2));
	if (ifree1)
		free(str1);
	if (ifree2)
		free(str2);
	return (str3);
}

char	*ft_strdup_free(char *src, int ifree)
{
	char		*dest;
	size_t		i;

	dest = malloc(sizeof(char) * (len(src) + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	if (ifree)
		free(src);
	return (dest);
}

char	*ft_substr_free(char *s, unsigned int start, size_t lenght, int ifree)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if ((len(s) == 1 && s[0] == '\n') || !lenght || len(s) < start)
	{
		if (ifree)
			free(s);
		return (ft_strdup_free("\0", 0));
	}
	str = malloc(sizeof(char) * (lenght + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < lenght && s[i])
		str[i++] = s[start++];
	str[i] = '\0';
	if (ifree)
		free(s);
	return (str);
}

int		find_quotes(char *cmd, int i, char c)
{
	if (!(cmd[i] == '\'' || cmd[i] == '\"'))
		return(i);
	i++;
	while (cmd[i] != c)
		i++;
	return(i);
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

int		is_maj(char c)
{
	if ((c > 64) && (c < 91))
		return (1);
	if ((c > 96) && (c < 123))
		return (1);
	return (0);
}

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

