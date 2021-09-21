/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 15:09:55 by ambelkac          #+#    #+#             */
/*   Updated: 2021/08/10 14:51:17 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	len_space(char *str)
// {
// 	int				i;

// 	i = 0;
// 	while (str[i] && str[i] != ' ')
// 		++i;
// 	return (i);
// }

// char	*cut_cmd(char *cmd)
// {
// 	char	*simple_cmd;

// 	simple_cmd = malloc(sizeof(char) * len_space(cmd) + 1);
// 	simple_cmd = ft_strncpy(simple_cmd, cmd, len_space(cmd));
// 	return (simple_cmd);
// }

// int	invalid_cmd(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] != ' ' || cmd[i] != '\n')
// 			return (0);
// 		++i;
// 	}
// 	return (1);
// }

// char	*path_parse(t_cmd_lst *cmds, char *cmd)
// {
// 	int		i;
// 	int		fd;
// 	char	*path;

// 	i = 0;
// 	if (invalid_cmd(cmd))
// 		return (NULL);
// 	while (cmds->paths[i])
// 	{
// 		if (cmd[0] != '/')
// 			path = cncat(cncat(cmds->paths[i], "/", 0, 0), cmd, 0, 0);
// 		else
// 			path = ft_strdup_free(cmd, 0);
// 		fd = open(path, O_RDONLY);
// 		if (fd != -1)
// 		{
// 			close(fd);
// 			return (path);
// 		}
// 		free(path);
// 		++i;
// 	}
// 	return (NULL);
// }
