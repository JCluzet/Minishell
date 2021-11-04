/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:17:22 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/03 20:26:54 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int		manage_heredoc(char *limit)
{
		char	*line;

	int		fd;

	fd = open("/tmp/tmp_heredoc", O_RDWR | O_TRUNC);
	if (fd == -1)
		fd = open("tmp/tmp_heredoc", O_RDWR | O_CREAT, 0666);
	line = NULL;
	write(1, ">", 1);
	get_next_line(0, &line);
	while (ft_strncmp(limit, line, len(limit)))
	{
		write(fd, line, len(line));
		free(line);
		line = NULL;
		write(fd, "\n", 1);
		write(1, ">", 1);
		get_next_line(0, &line);
	}
	close(fd);
	fd = open("/tmp/.tmp_heredoc", O_RDONLY);
	return (fd);
}

int			open_outfile(char *path, int in)
{
	int		fd;

	if (in == 1)
		fd = open(path, O_RDWR | O_TRUNC);
	else
		fd = open(path, O_RDWR | O_APPEND);
	if (fd == -1)
		fd = open(path, O_RDWR | O_CREAT, 0666);
	return (fd);
}

int		open_infile(char *path, int out)
{
	int		fd;

	if (out == 2)
		fd = manage_heredoc(path);
	else
		fd = open(path, O_RDONLY);
	if (fd == -1)
		printf("no such file or directory: %s\n", path);
	return (fd);
}

int			manage_redir_fd(t_cmd_lst *cmd, char **paths, int in, int out)
{
	int		fd;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (out)
		{
			fd = open_outfile(paths[i], in);
			if (fd == -1)
				return (1);
			add_fd_to_stack(cmd, fd);
			dup2(fd, 1);
		}
		if (in)
		{
			fd = open_infile(paths[i], out);
			if (fd == -1)
				return (1);
			add_fd_to_stack(cmd, fd);
			dup2(fd, 0);
		}
		++i;
	}
	return (0);
}

int			dispatch_redir_types(t_cmd_lst *cmds)
{
	int		fd;

	if (cmds->redir_ins)
		if (manage_redir_fd(cmds, cmds->redir_outs, 1, 0)) // THE YOSEPH INVERTION LETS GO
			return (1);
	if (cmds->reddir_heredoc)
		if (manage_redir_fd(cmds, cmds->reddir_heredoc, 2, 0))
			return (4);
	if (cmds->redir_outs)
		if (manage_redir_fd(cmds, cmds->redir_ins, 0, 1))
			return (2);
	if (cmds->reddir_append)
		if (manage_redir_fd(cmds, cmds->reddir_append, 0, 2))
			return (3);
	return (0);
}
