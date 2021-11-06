/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:29:46 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/06 18:29:07 by ambelkac         ###   ########.fr       */
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
		if (str[i] != '"' && str[i] != '\'')
			write(1, &str[i], 1);
		++i;
	}
}

void	putstr_quoteless(char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '"')
			++j;
		if (str[i] == '\'')
			++k;
		++i;
	}
	if (j > 2 || k > 2)
	{
		putstr_skipquotes(str);
		return ;
	}
	if (str[len(str) - 1] == '"' || str[len(str) - 1] == '\'')
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

int		is_dash_n_option(char *option)
{
	int		i;

	i = 1;
	if (option[0] != '-' && len(option) < 2)
		return (1);
	while (option[i] && option[i] == 'n')
	{
		++i;
	}
	if (option[i])
		return (1);
	return (0);
}

void	echo(t_sdata *sdata)
{
	if (tablen(sdata->cmds->argv) == 1)
	{
		write(1, "\n", 1);
		sdata->lrval = 0;
		return ;
	}
	if (!ft_strncmp(sdata->cmds->argv[1], "$?", 2) && len(sdata->cmds->argv[1]) == 2)
	{
		printf("%d\n", sdata->lrval);
		return ;
	}
	sdata->lrval = 0;
	if (!is_dash_n_option(sdata->cmds->argv[1]))
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
