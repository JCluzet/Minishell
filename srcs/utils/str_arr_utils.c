/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 15:07:24 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/04 22:39:30 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**new_arr(char *str)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 2);
	arr[0] = ft_strdup_free(str, 1);
	arr[1] = NULL;
	return (arr);
}

char	**extend_arr(char **arr, char *str)
{
	int			i;
	char		**n_arr;

	i = 0;
	n_arr = malloc(sizeof(char *) * (tablen(arr) + 2));
	while (arr[i])
	{
		n_arr[i] = arr[i];
		++i;
	}
	n_arr[i] = ft_strdup_free(str, 0);
	n_arr[i + 1] = NULL;
	free(arr);
	return (n_arr);
}

char	**cncat_arr(char **arr, char *str)
{
	int				i;

	i = 0;
	if (!arr)
		return (new_arr(str));
	else
		return (extend_arr(arr, str));
}

char	**remove_str_from_arr(char **arr, char *str)
{
	char	**n_arr;
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	name = get_env_var_name_from_arg(str);
	n_arr = malloc(sizeof(char *) * (tablen(arr) + 1));
	while (arr[i])
	{
		if (!ft_strncmp(name, arr[i], len(name)) && len(name) == lenequal(arr[i]))
		{
			free(arr[i]);
			++i;
			continue;
		}
		n_arr[j] = ft_strdup_free(arr[i], 1);
		++i;
		++j;
	}
	free(arr);
	n_arr[j] = NULL;
	free(name);
	return (n_arr);
}

char	**dup_arr(char **arr)
{
	char	**n_arr;
	int		len;
	int		i;
	i = 0;

	if (!arr)
		return (NULL);
	len = tablen(arr);
	n_arr = malloc(sizeof(char *) * (1 + len));
	while (i < len)
	{
		n_arr[i] = ft_strdup_free(arr[i], 0);
		++i;
	}
	n_arr[i] = NULL;
	return (n_arr);
}