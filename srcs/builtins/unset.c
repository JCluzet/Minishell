/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 17:39:08 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/26 12:54:21 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shell_unset(t_sdata *sdata)
{
	char	**n_env;
	int		i;

	if (sdata->cmds->argv[1] && (is_env_var_valid(sdata->cmds->argv[1], 1)))
	{
		sdata->lrval = 1;
		return ;
	}
	if (!sdata->cmds->argv[1] || !does_env_var_exist(sdata->env_lst, sdata->cmds->argv[1]))
	{
		sdata->lrval = 0;
		return ;
	}
	sdata->env = remove_str_from_arr(sdata->env, sdata->cmds->argv[1]);
	sdata->env_lst = remove_elem(sdata->env_lst, sdata->cmds->argv[1]);
	sdata->lrval = 0;
}

int		usage_unset(char ***env, char *var)
{
	char	**n_env;
	int		i;

	if (!is_env_var_valid(var, 1))
		return (1);
	if (get_idx_var_in_env(*env, var) == -1)
		return (0);
	n_env = malloc(sizeof(char *) * (tablen(*env) - 1));
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, len(var)))
			n_env[i] = (*env)[i];
		++i;
	}
	n_env[i] = NULL;
	free(*env);
	*env = n_env;
	return (0);
}