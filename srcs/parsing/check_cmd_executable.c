/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_executable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:24:10 by ambelkac          #+#    #+#             */
/*   Updated: 2021/09/21 19:54:27 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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
			path = cncat(cncat(paths[i], "/", 0, 0), cmd, 0, 0);
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

	fd = open(cmd + 2, O_RDONLY);
	if (fd == -1)
		return (NULL);
	else
		return (cmd);
}

// If cmd has a path to binary from path, return cmd_path or else NULL
char	*is_cmd_executable(char *cmd, t_sdata *sdata)
{
	char	**paths;
	char	*abs_cmd;

	if (!ft_strncmp(cmd, "./", 2))
		return (does_binary_file_exists(cmd));
	paths = get_paths_from_env(sdata->env_lst);
	if (!paths)
		return (NULL);
	abs_cmd = is_cmd_in_path(cmd, paths);
	free_arr(paths);
	printf("cmd_path : %s\n\n", abs_cmd);
	return (abs_cmd);
}