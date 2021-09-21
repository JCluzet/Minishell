/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:41:54 by ambelkac          #+#    #+#             */
/*   Updated: 2021/09/21 20:57:47 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **argv, char **env)
{
	t_sdata		sdata;

	if (ac != 1)
	{
		write(1, "Minishell can't have more than 0 argument\n", 43);
		return (0);
	}
	allocate_sdata(&sdata, env);
	shell_loop(&sdata);
	deallocate_sdata(&sdata);
}
