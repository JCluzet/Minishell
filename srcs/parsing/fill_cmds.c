/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:58:41 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 02:05:33 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_cmds(t_sdata *data, t_cmd_lst *cmds, char *cmd)
{
	cmd = replace_dollars(cmd, data);
	malloc_and_stock_redir(cmds, cmd);
	printf("\ncmd >> |%s|", cmd);
	cmd = rmv_rdr_from_cmd(cmd);
	printf("\ncmdapres >> |%s|", cmd);
	cmds->argv = split_arg(cmd);
	if (cmds->argv[0])
		cmds->cmd = ft_strdup_free(cmds->argv[0], 0);
	cmds->cmd_path = NULL;
	cmds->builtin_idx = is_builtin(cmds->cmd);
}
