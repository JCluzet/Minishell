/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:29:46 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/25 14:40:14 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// write tout les arguments de la cmd >>  pas seulement le 1

void	putstr_skipquotes(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '"')
			write(1, &str[i], 1);
		++i;
	}
}

void	putstr_quoteless(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"')
			++j;
		++i;
	}
	if (j > 2)
	{
		putstr_skipquotes(str);
		return ;
	}
	if (str[len(str) - 1] == '"')
		write(1, str + 1, len(str) - 2);
	else
		write(1, str + 1, len(str) - 1);
}

void	display_every_arg(char **argv, int start)
{
	int		i;

	i = start;
	while (argv[i])
	{
		if (argv[i][0] == '"' || argv[i][0] == '\'')
			putstr_quoteless(argv[i]);
		else
			write(1, argv[i], len(argv[i]));
		write(1, " ", 1);
		++i;
	}
}

void	echo(t_sdata *sdata)
{
	sdata->lrval = 0;
	if (tablen(sdata->cmds->argv) == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	if (!ft_strncmp(sdata->cmds->argv[1], "$?", 2) && len(sdata->cmds->argv[1]) == 2)
	{
		printf("%d\n", sdata->lrval);
		return ;
	}
	if (!ft_strncmp(sdata->cmds->argv[1], "-n", 2) && len(sdata->cmds->argv[1]) == 2)
	{
		if (tablen(sdata->cmds->argv) == 2)
			return ;
		display_every_arg(sdata->cmds->argv, 2);
		return ;
	}
	else
		display_every_arg(sdata->cmds->argv, 1);
	write(1, "\n", 1);
}
