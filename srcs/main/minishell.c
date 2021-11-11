/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:41:54 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 15:46:31 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **argv, char **env)
{
	t_sdata		sdata;

	(void)argv;
	if (ac != 1)
	{
		write(1, "Minishell can't have more than 0 argument\n", 43);
		return (0);
	}
	allocate_sdata(&sdata, env);
	assign_signals_handler();
	shell_loop(&sdata);
	deallocate_sdata(&sdata);
}
