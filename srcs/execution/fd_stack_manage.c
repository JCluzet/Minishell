/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_stack_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:36:15 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 15:08:14 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*extend_fd_stack(int *fd_stack, int fd_len, int fd)
{
	int		i;
	int		*nfd_stack;

	i = 0;
	nfd_stack = malloc(sizeof(int) * (fd_len + 1));
	if (!nfd_stack)
		return (NULL);
	while (i < fd_len)
	{
		nfd_stack[i] = fd_stack[i];
		++i;
	}
	nfd_stack[i] = fd;
	return (nfd_stack);
}

void	add_fd_to_stack(t_cmd_lst *cmds, int fd)
{
	if (!cmds->fd_stack)
	{
		cmds->fd_stack = malloc(sizeof(int));
		if (!cmds->fd_stack)
		{
			cmds->fd_nbr = 0;
			return ;
		}
		cmds->fd_stack[0] = fd;
		cmds->fd_nbr = 1;
	}
	else
	{
		cmds->fd_stack = extend_fd_stack(cmds->fd_stack, cmds->fd_nbr, fd);
		if (!cmds->fd_stack)
		{
			cmds->fd_nbr = 0;
			return ;
		}
		(cmds->fd_nbr)++;
	}
}

void	clear_fd_stack(t_cmd_lst *cmds)
{
	int		i;

	i = 0;
	while (i < cmds->fd_nbr)
	{
		close(cmds->fd_stack[i]);
		++i;
	}
	free(cmds->fd_stack);
	cmds->fd_stack = NULL;
	cmds->fd_nbr = 0;
}
