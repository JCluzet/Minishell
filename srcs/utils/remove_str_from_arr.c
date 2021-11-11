/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_str_from_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:22:43 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 17:11:49 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	transfer_arr(char **arr, char **n_arr, char *name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		if (!ft_strncmp(name, arr[i], len(name))
			&& len(name) == lenequal(arr[i]))
		{
			free(arr[i++]);
			continue ;
		}
		n_arr[j] = ft_strdup_free(arr[i], 1);
		++j;
		++i;
	}
	n_arr[j] = NULL;
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
	if (!n_arr)
		return (NULL);
	transfer_arr(arr, n_arr, name);
	free(arr);
	free(name);
	return (n_arr);
}

char	*str_find_var(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (!is_in_set(str[i], ENV_CHAR_LIST))
			break ;
		i++;
	}
	if (i == 0)
		return (NULL);
	tmp = malloc(sizeof(char *) * (i + 1));
	return (ft_strncpy(tmp, str, i));
}
