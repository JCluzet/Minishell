/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:44:55 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 18:36:45 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**set_word_in_tab(char **arr, char *line, int i)
{
	arr[0] = malloc(sizeof(char) * (i + 1));
	if (!arr[0])
	{
		free(arr);
		return (NULL);
	}
	arr[0] = ft_strncpy(arr[0], line, i);
	arr[1] = malloc(sizeof(char) * (len(line) - i + 1));
	if (!arr[1])
	{
		free(arr);
		return (NULL);
	}
	arr[1] = ft_strncpy(arr[1], line + i + 1, len(line) - i - 1);
	arr[2] = NULL;
	return (arr);
}

char	**split_env(char *line, char sep)
{
	char	**arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(char *) * 3);
	if (!arr)
		return (NULL);
	while (line[i])
	{
		if (line[i] == sep)
		{
			arr = set_word_in_tab(arr, line, i);
			return (arr);
		}
		else
			++i;
	}
	return (NULL);
}
