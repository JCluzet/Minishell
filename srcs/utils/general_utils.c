/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:32:45 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 18:53:33 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_bzero(size_t n)
{
	void	*ptr;
	int		i;

	ptr = malloc(n);
	if (!ptr)
		return (NULL);
	i = 0;
	if (!ptr)
		return (NULL);
	while (i < n)
	{
		((char *)ptr)[i] = 0;
		++i;
	}
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		++i;
	}
	return ((unsigned char)s1[i] - s2[i]);
}

int	nbr_of_word(char *av, char sep)
{
	int				i;
	int				count;

	count = 1;
	i = 0;
	if (!av || !av[i])
		return (0);
	while (av[i])
	{
		if (av[i] != sep)
		{
			while (av[i] && av[i] != sep)
				++i;
			++count;
			continue ;
		}
		++i;
	}
	return (count);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	find_quotes(char *cmd, int i, char c)
{
	if (!(cmd[i] == '\'' || cmd[i] == '\"'))
		return (i);
	i++;
	while (cmd[i] != c)
		i++;
	return (i);
}
