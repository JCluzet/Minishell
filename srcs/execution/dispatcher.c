/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:11:06 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 17:10:37 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void (*builtins_array[7])(t_sdata *) = {display_env, shell_export, shell_unset, pwd,
	echo, shell_cd, shell_exit};

void		child_handler(int signum)
{
	(void)signum;
	putstr_err("Quit (core dumped)\n");
	exit(131);
}

int		manage_pipe_dups(t_cmd_lst *cmds, pid_t pid, int *fd)
{
	if (!pid)
		signal(SIGQUIT, child_handler);
	if (cmds->next)
		if (!pid)
		{
			close(fd[0]);
			dup2(fd[1], 1);
		}
	if (!pid)
		if (dispatch_redir_types(cmds))
			return (1);
	return (0);
}

void		invalid_cmd(t_sdata *sdata, t_cmd_lst *cmds)
{
	putstr_err(cmds->cmd);
	putstr_err(": command not found\n");
	deallocate_sdata(sdata);
	exit(1);
}

int			execute_builtins(t_sdata *sdata, int *fd, int save_stdout)
{
	if (sdata->cmds->next)
		dup2(fd[1], 1);
	if (dispatch_redir_types(sdata->cmds))
	{
		sdata->lrval = 1;
		sdata->cmds = sdata->cmds->next;
		return (1);
	}
	(builtins_array)[sdata->cmds->builtin_idx](sdata);
	dup2(save_stdout, 1);
	if (sdata->cmds->next)
	{
		close(fd[1]);
	}
	clear_fd_stack(sdata->cmds);
	return (0);
}

int			execute_binary(t_sdata *sdata, int *fd, int save_stdin)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (manage_pipe_dups(sdata->cmds, pid, fd))
	{
		sdata->lrval = 1;
		sdata->cmds = sdata->cmds->next;
		if (!pid)
			error_print_free(0, NULL, sdata);
		return (1);
	}
	if (!pid)
	{
		if (execve(sdata->cmds->cmd_path, sdata->cmds->argv, sdata->env))
			invalid_cmd(sdata, sdata->cmds);
	}
	else
		waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
	{
		putstr_err("Quit (core dumped)\n");
		sdata->lrval = 131;
	}
	else
		sdata->lrval = WEXITSTATUS(status);
	return (0);
}

void		invalid_cmd_path_error(t_sdata *sdata)
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

void		execution_dispatcher(t_sdata *sdata, t_cmd_lst *cmds)
{
	int		fd[2];
	int		last_fdin;

	last_fdin = 0;
	while (sdata->cmds)
	{
		sdata->cmds->save_stdin = sdata->save_stdin;
		if (sdata->cmds->next)
			pipe(fd);
		if (sdata->cmds->builtin_idx < 7 && sdata->cmds->builtin_idx != -1)
		{
			if (execute_builtins(sdata, fd, sdata->save_stdout))
				continue ;
		}
		else if (sdata->cmds->cmd_path)
		{
			if (execute_binary(sdata, fd, sdata->save_stdin))
				continue ;
		}
		else
			invalid_cmd_path_error(sdata);
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