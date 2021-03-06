/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:17:22 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 15:43:45 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manage_heredoc(char *limit, int l_fd_in, int save_stdin)
{
	char	*line;
	int		fd;

	dup2(save_stdin, 0);
	fd = open("/tmp/.tmp_heredoc", O_RDWR | O_TRUNC);
	if (fd == -1)
		fd = open("/tmp/.tmp_heredoc", O_RDWR | O_CREAT, 0666);
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
	dup2(l_fd_in, 0);
	return (fd);
}

int	open_outfile(char *path, int in)
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

int	open_infile(t_cmd_lst *cmds, char *path, int out)
{
	int		fd;

	if (out == 2)
		fd = manage_heredoc(path, cmds->last_fd_in, cmds->save_stdin);
	else
		fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		putstr_err("no such file or directory: ");
		putstr_err(path);
		putstr_err("\n");
	}	
	cmds->last_fd_in = fd;
	return (fd);
}

int	dispatch_redir_types(t_cmd_lst *cmds)
{
	if (priority_redir_in(cmds))
		return (1);
	if (priority_redir_out(cmds))
		return (1);
	return (0);
}
