/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_word_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:26:09 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 00:29:54 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_sep_char(char *av, char sep, int *i)
{
	while (av[*i] && av[*i] != sep)
		++(*i);
}

char	*put_word_in_arr(char *av, int i, int j, int save)
{
	char	*str;

	(void)j;		// rajout pour le flag -wall
	str = malloc(sizeof(char) * (i - save + 1));
	if (!str)
		return (NULL);
	str = ft_strncpy(str, av + save, i - save);
	return(NULL); // jai add ca 
}

char	**str_to_word_arr(char *av, char sep)
{
	t_split_var		var;
	char			**arr;

	if (!av || av[0] == 0 || nbr_of_word(av, sep) == 0)
		return (NULL);
	arr = ft_bzero(sizeof(char *) * (nbr_of_word(av, sep) + 1));
	if (!arr)
		return (NULL);
	var.i = 0;
	var.j = 0;
	var.save = 0;
	while (av[var.i])
	{
		if (av[var.i] != sep)
		{
			var.save = var.i;
			skip_sep_char(av, sep, &(var.i));
			arr[var.j] = put_word_in_arr(av, var.i, var.j, var.save);
			++(var.j);
		}
		else
			++(var.i);
	}
	return (arr);
}
