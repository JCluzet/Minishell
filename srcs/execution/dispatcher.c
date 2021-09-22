/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:11:06 by ambelkac          #+#    #+#             */
/*   Updated: 2021/09/22 00:54:34 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void (*builtins_array[7])(t_sdata *) = {display_env, shell_export, shell_unset, pwd,
	echo, shell_cd, shell_exit};

void		execution_dispatcher(t_sdata *sdata)
{
	pid_t	pid;

	if (!sdata->cmds)
		return ;
	if (sdata->cmds->builtin_idx < 7 && sdata->cmds->builtin_idx != -1)
		(builtins_array)[sdata->cmds->builtin_idx](sdata);
	else if (sdata->cmds->cmd_path)
	{
		pid = fork();                          // Quest ce que c'est que ca ? 
		if (!pid)
		{
			execve(sdata->cmds->cmd_path, sdata->cmds->argv, sdata->env);
		}
		else
		{
			waitpid(-1, NULL, 0);
		}
	}
}