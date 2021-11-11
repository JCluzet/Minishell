/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:32:54 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 15:47:17 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	invalid_cmd(t_sdata *sdata, t_cmd_lst *cmds)
{
	putstr_err(cmds->cmd);
	putstr_err(": command not found\n");
	deallocate_sdata(sdata);
	exit(1);
}

int	execute_builtins(t_sdata *sdata, int *fd, int save_stdout)
{
	static void	(*builtins_array[7])(t_sdata *)
		= {display_env, shell_export, shell_unset,
		pwd, echo, shell_cd, shell_exit};

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

void	get_child_return_value(t_sdata *sdata, int status)
{
	if (WIFSIGNALED(status))
	{
		putstr_err("Quit (core dumped)\n");
		sdata->lrval = 131;
	}
	else
		sdata->lrval = WEXITSTATUS(status);
}

int	execute_binary(t_sdata *sdata, int *fd)
{
	pid_t	pid;
	int		status;

	status = 0;
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
	get_child_return_value(sdata, status);
	return (0);
}
