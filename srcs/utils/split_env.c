/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:44:55 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 15:50:46 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		**split_env(char *line, char sep)
{
	char	**arr;
	int		i;
	int		save;

	arr = malloc(sizeof(char *) * 3);
	while (line[i])
	{
		if (line[i] == sep)
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
			arr[1] = ft_strncpy(arr[1], line + i, len(line) - 1);
			arr[2] = NULL;
			return (arr);
		}
		else
			++i;
	}
	return (NULL);
}