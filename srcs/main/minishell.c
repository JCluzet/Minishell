/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:41:54 by ambelkac          #+#    #+#             */
/*   Updated: 2021/08/20 02:03:29 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **argv, char **env)
{
	t_sdata		sdata;

	allocate_sdata(&sdata, env);
	shell_loop(&sdata);
	deallocate_sdata(&sdata);
}
