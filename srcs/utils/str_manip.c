/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:48:50 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/29 15:51:40 by jcluzet          ###   ########.fr       */
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
	i = 0;
	while (i < lenght && s[i])
		str[i++] = s[start++];
	str[i] = '\0';
	if (ifree)
		free(s);
	return (str);
}

char 	*replace_dollars(char *str, t_sdata *sdata)
{
	int i;
	char *newcmd;
	char *tmp;
	int card;
	int j;
	int u;

	u = 0;
	j = 0;
	i = 0;
	card = strlen_pathcmd(sdata, str);
	if (card == -1)
		return (NULL);
	newcmd = malloc(sizeof(char) * (card + 1));
	//printf("\n\nMalloc de %d\n", card);
	while (j < card)
	{
		if (str[i] == '$' && ( i == 0 || (str[i-1] != '\\') ))
		{
			tmp = get_env_var_from_name(sdata->env_lst, str_x(str + i + 1));
			while (tmp[u])
			{
				newcmd[j] = tmp[u];
				j++;
				u++;
			}
			u = 0;
			i += len_x(str + i, ' ') - 1;
		}
		else
		{
			newcmd[j] = str[i];
			j++;
		}
		i++;
	}
	newcmd[j] = '\0';
	//printf("\n\n>>%s<<\n", newcmd);
	return(newcmd);
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
