/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:58:41 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/22 13:16:44 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_cmds(t_cmd_lst *cmds, char *cmd)
{
	cmds->argv = split_thespace(cmd, ' ');
	if (cmds->argv)
		cmds->cmd = ft_strdup_free(cmds->argv[0], 0);
	cmds->cmd_path = NULL;
	if (cmds->argv)
		cmds->builtin_idx = is_builtin(cmds->argv[0]); 
	else
		cmds->builtin_idx = -1;
}
