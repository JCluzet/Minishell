/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:48:50 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/13 16:37:26 by ambelkac         ###   ########.fr       */
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

	if (!src)
		return (NULL);
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
	if ((len(s) == 1 && s[0] == '\n') || !lenght || len(s) < (int)start)
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
