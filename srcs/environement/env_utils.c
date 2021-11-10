/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:51:36 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 17:53:20 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_var_from_name(t_env_lst *list, char *name)
{
	if (name == NULL)
		return (NULL);
	while (list)
	{
		if (!ft_strncmp(list->name, name,
				len(name)) && len(name) == len(list->name))
			return (list->var);
		list = list->next;
	}
	return (NULL);
}

char	*get_var_in_env(char **env, char *var)
{
	int			i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len(var)))
			return (env[i]);
		++i;
	}
	return (NULL);
}

char	*get_env_var_name_from_arg(char *arg)
{
	char	**line;
	char	*name;
	int		i;

	i = 1;
	line = str_to_word_arr(arg, '=');
	name = line[0];
	while (line[i])
	{
		free(line[i]);
		++i;
	}
	free(line);
	return (name);
}
