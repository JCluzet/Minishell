/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:11:06 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/22 13:34:44 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void (*builtins_array[7])(t_sdata *) = {display_env, shell_export, shell_unset, pwd,
	echo, shell_cd, shell_exit};

void	manage_fd_dups(t_sdata *sdata, t_cmd_lst *cmds, int *fd)
{
	pipe(fd);
	dup2(fd[1], 1);

	// Cascade Dup redirection inward

	// Cascade Dup redicrection outward

	// 
}

void		execution_dispatcher(t_sdata *sdata, t_cmd_lst *cmds)
{
	pid_t	pid;
	int		i;
	int		*fd;

	i = 0;
	while (cmds)
	{
		printf("EXECUTION : %s\n\n", cmds->cmd); 
		if (cmds->builtin_idx < 7 && cmds->builtin_idx != -1)
			(builtins_array)[cmds->builtin_idx](sdata);
		else if (cmds->cmd_path)
		{
			pid = fork();
			if (cmds->next)
			{
				pipe(fd);
			}
			if (!pid)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				execve(cmds->cmd_path, cmds->argv, sdata->env);
			}
			else
			{
				close(fd[1]);
				dup2(fd[0], 0);
				waitpid(-1, NULL, 0);
			}
		}
		cmds = cmds->next;
	}
}