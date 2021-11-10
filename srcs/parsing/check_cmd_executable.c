/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_executable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:24:10 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 00:20:37 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

char	**get_paths_from_env(t_env_lst *env)
{
	char	*path;

	path = get_env_var_from_name(env, "PATH");
	if (!path)
		return (NULL);
	return (str_to_word_arr(path, ':'));
}

char	*is_cmd_in_path(char *cmd, char **paths)
{
	char	*path;
	int		i;
	int		fd;

	i = 0;
	while (paths[i])
	{
		if (cmd[0] != '/')
			path = cncat(cncat(paths[i], "/", 0, 0), cmd, 1, 0);
		else
			path = ft_strdup_free(cmd, 0);
		fd = open(path, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			return (path);
		}
		free(path);
		++i;
	}
	return (NULL);
}

char	*does_binary_file_exists(char *cmd)
{
	int	fd;

	if (!ft_strncmp(cmd, "./", 2))
		fd = open(cmd + 2, O_RDONLY);
	else
		fd = open(cmd, O_RDONLY);
	if (fd == -1)
		return (NULL);
	else
	{
		close(fd);
		return (cmd);
	}
}

char	*is_cmd_executable(char *cmd, t_sdata *sdata)
{
	char	**paths;
	char	*abs_cmd;

	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
		return (does_binary_file_exists(cmd));
	paths = get_paths_from_env(sdata->env_lst);
	if (!paths)
		return (NULL);
	abs_cmd = is_cmd_in_path(cmd, paths);
	free_arr(paths);
	return (abs_cmd);
}

void (*builtins[7])(t_sdata *) = {display_env, shell_export, shell_unset, pwd,
	echo , shell_cd, shell_exit};

static const char *g_builtins_mask[7] = {"env", "export", "unset", "pwd", "echo", "cd", "exit"};

int	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (-1);
	while (i < 7)
	{
		if (!ft_strncmp(g_builtins_mask[i], cmd, len(g_builtins_mask[i])) && len(cmd) == len(g_builtins_mask[i]))
			return (i);
		++i;
	}
	if (i == 7)
		return (-1);
	return (i);
}