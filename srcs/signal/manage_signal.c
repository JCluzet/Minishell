/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:55:18 by amine             #+#    #+#             */
/*   Updated: 2021/11/08 20:08:48 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		handler(int signum)
{
	rl_on_new_line();
}

void		assign_signals_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
}