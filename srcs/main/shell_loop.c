/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:01:28 by ambelkac          #+#    #+#             */
/*   Updated: 2021/09/22 00:23:27 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_close_cmd(t_sdata *sdata, char *line)
{
	if (!line)
	{
		deallocate_sdata(sdata);
		usage_exit(NULL);
	}
	return (0);
}

int	shell_loop(t_sdata *sdata)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("\033[33m$ ➜\033[00m ");
		add_history(line);
		if (line[0] == 0 || empty_str(line))
			continue ;
		sdata->cmds = parse_line(sdata, line);
		if (check_error(sdata->cmds) == 0)
			execution_dispatcher(sdata);
		deallocate_cmd_elem(sdata->cmds);
		sdata->cmds = NULL;
		if (is_close_cmd(sdata, line))
			break;
	}
	return (sdata->lrval);
}
