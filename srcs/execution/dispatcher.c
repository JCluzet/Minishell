/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:11:06 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/05 17:27:10 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void (*builtins_array[7])(t_sdata *) = {display_env, shell_export, shell_unset, pwd,
	echo, shell_cd, shell_exit};

int		manage_pipe_dups(t_cmd_lst *cmds, pid_t pid, int *fd)
{
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

void		invalid_cmd(t_sdata *sdata, t_cmd_lst *cmds, int save_stdout)
{
	dup2(save_stdout, 1);
	printf("%s: command not found\n", cmds->cmd);
	//  Free everything
	exit(1);
}

void		execution_dispatcher(t_sdata *sdata, t_cmd_lst *cmds)
{
	int		fd[2];
	pid_t	pid;
	int		save_stdin;
	int		save_stdout;
	int		status;

	status = 0;
	save_stdin = dup(0);
	save_stdout = dup(1);
	while (cmds)
	{
		cmds->save_stdin = save_stdin;
		if (cmds->next)
			pipe(fd);
		if (cmds->builtin_idx < 7 && cmds->builtin_idx != -1)
		{	
			if (cmds->next)
				dup2(fd[1], 1);
			if (dispatch_redir_types(cmds))
			{
				sdata->lrval = 1;
				cmds = cmds->next;
				continue;
			}
			if (!cmds->next)
				dup2(save_stdout, 1);
			(builtins_array)[cmds->builtin_idx](sdata);
			if (cmds->next)
			{
				dup2(save_stdout, 1);
				close(fd[1]);
			}
			clear_fd_stack(cmds);
		}

		else if (cmds->cmd_path)
		{
			pid = fork();
			if (manage_pipe_dups(cmds, pid, fd))
			{
				sdata->lrval = 1;
				cmds = cmds->next;
				continue;
			}
			if (!pid)
			{
				if (execve(cmds->cmd_path, cmds->argv, sdata->env))
					invalid_cmd(sdata, cmds, save_stdin);
			}
			else
				waitpid(-1, &status, 0);
			sdata->lrval = WEXITSTATUS(status);
		}

		else // Invalid cmd path error management
		{
			if (cmds->argv[0][0] == '.' || cmds->argv[0][0] == '/')
				printf("no such file or directory: %s\n", cmds->argv[0]);
			else
				printf("command not found: %s\n", cmds->argv[0]);
			sdata->lrval = 127;
		}

		if (cmds->next)
		{
			close(fd[1]);
			dup2(fd[0], 0);
		}
		// if (cmds->next && !cmds->next->next)
		// {
		// 	close(fd[1]);
		// 	dup2(save_stdout, 1);
		// }
		cmds = cmds->next;
	}
	dup2(save_stdin, 0);
	close(save_stdin);
	close(save_stdout);
}