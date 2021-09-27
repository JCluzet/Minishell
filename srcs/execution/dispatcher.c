/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:11:06 by ambelkac          #+#    #+#             */
/*   Updated: 2021/09/27 23:36:55 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void (*builtins_array[7])(t_sdata *) = {display_env, shell_export, shell_unset, pwd,
	echo, shell_cd, shell_exit};

void	manage_fd_dups(t_sdata sdata)
{
	// Cascade Dup redirection inward

	// Cascade Dup redicrection outward

	// 
}

void		execution_dispatcher(t_sdata *sdata)
{
	pid_t	pid;
	int		i;

	i = 0;
	// while (i < sdata->cmd_nbr)
	// {
		if (sdata->cmds->builtin_idx < 7 && sdata->cmds->builtin_idx != -1)
			(builtins_array)[sdata->cmds->builtin_idx](sdata);
		else if (sdata->cmds->cmd_path)
		{
			// manage_fd_dups();
			pid = fork();
			if (!pid)
			{
				execve(sdata->cmds->cmd_path, sdata->cmds->argv, sdata->env);
			}
			else
			{
				waitpid(-1, NULL, 0);
			}
		// }
	}
}