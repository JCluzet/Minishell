/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:52:22 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/06 01:05:01 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		env_var_additional_parsing(char *arg, int is_unset)
{
	int	i;
	int	counter;

	counter = 0;
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '=')
			++counter;
		if (counter > 0 && is_unset)
			return (0);
		if (counter > 1)
			return (0);
		++i;
	}
	return (1);
}

int		is_env_var_valid(char *arg, int is_unset)
{
	int	i;

	i = 1;
	if (!arg || (len(arg) == 0 && arg[0] == 0))
		return (1);
	if (!is_in_set(arg[0], FIRST_ENV_CHAR_LIST))
	{
		printf("'%s': not a valid identifier\n", arg);
		return (1);
	}
	while (arg[i])
	{
		if (!is_in_set(arg[i++], ENV_CHAR_LIST))
		{
			printf("'%s': not a valid identifier\n", arg);
			return (1);
		}
	}
	if (!env_var_additional_parsing(arg, is_unset))
	{
		printf("'%s': not a valid identifier\n", arg);
		return (1);
	}
	return (0);
}

int		does_env_var_exist(t_env_lst *env, char *var)
{
	char	*name;

	name = get_env_var_name_from_arg(var);
	while (env)
	{
		if (!ft_strncmp(env->name, name, len(name)) && len(name) == len(env->name))
		{
			free(name);
			return (1);
		}
		env = env->next;
	}
	free(name);
	return (0);
}

int		get_idx_var_in_env(char **env, char *var)
{
	int			i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, lenequal(var) && lenequal(env[i]) == lenequal(var)))
			return (i);
		++i;
	}
	return (-1);
}

char	*get_env_var_from_name(t_env_lst *list, char *name)
{
	//printf("\nYAL1.5>> |%s|\n", name);
	while (list)
	{
		if (!ft_strncmp(list->name, name, len(name)) && len(name) == len(list->name))
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