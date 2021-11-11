/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dispatcher.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:09:04 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 15:16:38 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	call_outfile(t_cmd_lst *cmd, char **paths, int out, int i)
{
	int	fd;

	fd = open_outfile(paths[i], out);
	if (fd == -1)
		return (1);
	add_fd_to_stack(cmd, fd);
	if (!cmd->fd_stack)
		return (1);
	dup2(fd, 1);
	return (0);
}

int	call_infile(t_cmd_lst *cmd, char **paths, int in, int i)
{
	int	fd;

	fd = open_infile(cmd, paths[i], in);
	if (fd == -1)
		return (1);
	add_fd_to_stack(cmd, fd);
	if (!cmd->fd_stack)
		return (1);
	dup2(fd, 0);
	return (0);
}

int	manage_redir_fd(t_cmd_lst *cmd, char **paths, int in, int out)
{
	int		fd;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (out)
			if (call_outfile(cmd, paths, out, i))
				return (1);
		if (in)
			if (call_infile(cmd, paths, in, i))
				return (1);
		++i;
	}
	return (0);
}

int	priority_redir_in(t_cmd_lst *cmds)
{
	if (cmds->type_last_rdr_in == 2)
	{
		if (cmds->redir_ins)
			if (manage_redir_fd(cmds, cmds->redir_outs, 1, 0))
				return (1);
		if (cmds->reddir_heredoc)
			if (manage_redir_fd(cmds, cmds->reddir_heredoc, 2, 0))
				return (4);
	}
	else
	{
		if (cmds->reddir_heredoc)
			if (manage_redir_fd(cmds, cmds->reddir_heredoc, 2, 0))
				return (4);
		if (cmds->redir_ins)
			if (manage_redir_fd(cmds, cmds->redir_outs, 1, 0))
				return (1);
	}
	return (0);
}

int	priority_redir_out(t_cmd_lst *cmds)
{
	if (cmds->type_last_rdr_out == 2)
	{
		if (cmds->redir_outs)
			if (manage_redir_fd(cmds, cmds->redir_ins, 0, 1))
				return (2);
		if (cmds->reddir_append)
			if (manage_redir_fd(cmds, cmds->reddir_append, 0, 2))
				return (3);
	}
	else
	{
		if (cmds->reddir_append)
			if (manage_redir_fd(cmds, cmds->reddir_append, 0, 2))
				return (3);
		if (cmds->redir_outs)
			if (manage_redir_fd(cmds, cmds->redir_ins, 0, 1))
				return (2);
	}
	return (0);
}
