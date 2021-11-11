/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 16:32:53 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 15:42:19 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Choose and stick to builtin prototype

void	update_env_cd(t_sdata *sdata, char *old_pwd)
{
	if (does_env_var_exist(sdata->env_lst, "OLDPWD"))
		usage_export_replace_var(sdata, cncat("OLDPWD=", old_pwd, 0, 1));
	if (does_env_var_exist(sdata->env_lst, "PWD"))
		usage_export_replace_var(sdata, cncat("PWD=", getcwd(NULL, 0), 0, 1));
}

char	*get_abs_path(char *path, int free_path)
{
	if ((len(path) == 1 && path[0] == '.')
		|| (len(path) == 2 && path[0] == '.' && path[1] == '.'))
		return (path);
	if (path[0] == '/')
		return (path);
	return (cncat(getcwd(NULL, 0), cncat("/", path, 0, free_path), 1, 1));
}

void	change_directory_home(t_sdata *sdata)
{
	char	*home_path;
	char	*abs_path;

	home_path = get_env_var_from_name(sdata->env_lst, "HOME");
	if (!home_path)
	{
		printf("bash: cd: HOME not set\n");
		sdata->lrval = 1;
		return ;
	}
	abs_path = get_abs_path(home_path, 0);
	sdata->lrval = 0;
	if (chdir(abs_path) == -1)
	{
		printf("bash: cd: %s:No such file or directory\n", home_path);
		sdata->lrval = 1;
	}
}

void	shell_cd(t_sdata *sdata)
{
	char	*abs_path;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (tablen(sdata->cmds->argv) == 1)
	{
		change_directory_home(sdata);
		update_env_cd(sdata, old_pwd);
		return ;
	}
	abs_path = get_abs_path(sdata->cmds->argv[1], 0);
	if (chdir(abs_path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n",
			sdata->cmds->argv[1]);
		sdata->lrval = 1;
		return ;
	}
	update_env_cd(sdata, old_pwd);
	sdata->lrval = 0;
}
