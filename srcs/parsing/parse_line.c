/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:08:47 by ambelkac          #+#    #+#             */
/*   Updated: 2021/09/21 00:16:21 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void (*builtins[7])(t_sdata *) = {display_env, shell_export, shell_unset, pwd,
	echo , shell_cd, shell_exit};

static const char *g_builtins_mask[7] = {"env", "export", "unset", "pwd", "echo", "cd", "exit"};


int	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return(-1);
	while (i < 7)
	{
		if (!ft_strncmp(g_builtins_mask[i], cmd, len(g_builtins_mask[i])))
			return (i);
		++i;
	}
	if (i == 7)
		return (-1);
	return (i);
}

char	*find_cmd_path(t_cmd_lst *cmd, char **paths)
{
	int		i;
	char	*path;
	int		fd;

	i = 0;
	if (!cmd)
		return (NULL);
	while (paths[i])
	{
		if (cmd->cmd[0] != '/')
			path = cncat(cncat(paths[i], "/", 0, 0), cmd->cmd, 0, 0);
		else
			path = ft_strdup_free(cmd->cmd, 0);
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

t_cmd_lst		*parse_line(t_sdata *sdata, char *line)
{
	t_cmd_lst *cmd;

	if (!line)
		return (NULL);
	cmd = fill_multi_cmds(line);
	// cmd = fill_cmds(line);
	if (cmd->builtin_idx > 6)
		cmd->cmd_path = find_cmd_path(cmd, sdata->bin_paths);
	return (cmd);
}

int		check_error(t_cmd_lst *cmds)
{
	if (!cmds)
		return(-1);
	if ((((cmds->builtin_idx > 6) && !cmds->cmd_path) || (cmds->builtin_idx == -1 && !cmds->cmd_path)) && cmds->argv)
	{
		write(1, "minishell: command not found: ", 31);
		write(1, cmds->cmd, len(cmds->cmd));
		write(1, "\n", 1);
	}
	return(0);
}
