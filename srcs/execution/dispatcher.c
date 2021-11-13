/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo <jo@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:11:06 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/13 15:15:29 by jo               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manage_pipe_dups(t_cmd_lst *cmds, pid_t pid, int *fd)
{
	if (!pid)
		signal(SIGQUIT, child_handler);
	if (cmds->next)
	{
		if (!pid)
		{
			dup2(fd[1], 1);
		}
	}
	if (!pid)
		if (dispatch_redir_types(cmds))
			return (1);
	return (0);
}

void	invalid_cmd_path_error(t_sdata *sdata)
{
	if (sdata->cmds->argv[0][0] == '.' || sdata->cmds->argv[0][0] == '/')
	{
		putstr_err("no such file or directory: ");
		putstr_err(sdata->cmds->cmd);
		putstr_err("\n");
	}
	else
	{
		putstr_err("command not found: ");
		putstr_err(sdata->cmds->cmd);
		putstr_err("\n");
	}
	sdata->lrval = 127;
}

int	valid_cmd_dispatch(t_sdata *sdata, int *fd)
{
	if (sdata->cmds->builtin_idx < 7 && sdata->cmds->builtin_idx != -1)
	{
		if (execute_builtins(sdata, fd, sdata->save_stdout))
			return (1);
	}
	else if (sdata->cmds->cmd_path)
	{
		if (execute_binary(sdata, fd))
			return (1);
	}
	else
		invalid_cmd_path_error(sdata);
	return (0);
}

void	execution_dispatcher(t_sdata *sdata)
{
	int		fd[2];
	int		last_fdin;

	last_fdin = 0;
	while (sdata->cmds)
	{
		sdata->cmds->save_stdin = sdata->save_stdin;
		if (sdata->cmds->next)
			pipe(fd);
		if (valid_cmd_dispatch(sdata, fd))
			continue ;
		if (last_fdin)
			close(last_fdin);
		if (sdata->cmds->next)
		{
			close(fd[1]);
			last_fdin = fd[0];
			dup2(fd[0], 0);
		}
		sdata->cmds = sdata->cmds->next;
	}
	dup2(sdata->save_stdin, 0);
}
