/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:11:06 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/25 16:45:43 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void (*builtins_array[7])(t_sdata *) = {display_env, shell_export, shell_unset, pwd,
	echo, shell_cd, shell_exit};

void	manage_pipe_dups(t_cmd_lst *cmds, pid_t pid, int *fd)
{
	if (cmds->next)
		if (!pid)
		{
			close(fd[0]);
			dup2(fd[1], 1);
		}
}

void		execution_dispatcher(t_sdata *sdata, t_cmd_lst *cmds)
{
	int		fd[2];
	pid_t	pid;
	int		i;
	int		save_stdin;
	int		save_stdout;

	save_stdin = dup(0);
	save_stdout = dup(1);
	i = 0;
	while (cmds)
	{
		if (cmds->next)
			pipe(fd);
		if (cmds->builtin_idx < 7 && cmds->builtin_idx != -1)
		{	
			if (cmds->next)
				dup2(fd[1], 1);
			(builtins_array)[cmds->builtin_idx](sdata);
			dup2(save_stdout, 1);
		}
		else if (cmds->cmd_path)
		{
			pid = fork();
			manage_pipe_dups(cmds, pid, fd);
			if (!pid)
				execve(cmds->cmd_path, cmds->argv, sdata->env);
			else
				waitpid(-1, NULL, 0);
		}
		if (cmds->next)
		{
			close(fd[1]);
			dup2(fd[0], 0);
		}
		cmds = cmds->next;
	}
	dup2(save_stdin, 0);
	close(save_stdin);
	close(save_stdout);
}