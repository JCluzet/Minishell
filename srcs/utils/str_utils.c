/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:44:56 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/19 00:27:40 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tablen(char **tab)
{
	int				i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		++i;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_number(char const *str, int i)
{
	int		count;

	count = 1;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[++i]))
		++count;
	return (count);
}

int	is_in_set(char c, char const *set)
{
	int		i;

	i = 0;
	if (!set[i])
		return (0);
	while (set[i])
	{
		if (c == set[i])
			return (1);
		++i;
	}
	return (0);
}

size_t	len(const char *str)
{
	int				i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int		len_x(char const *str, char c)
{
	int				i;
	
	i = 0;
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

char 	*str_x(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == ' ')
			str[i] = '\0';
		++i;
	}
	return (str);
}

int empty_str(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

int is_double_redir(char c, char c1)
{
	if ((c == '<' && c1 == '<') || (c == '>' && c1 == '>'))
		return (1);
	return(0);
}

int issep(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return(0);
}

int	isspace_behind(char *str, int i)
{
	int u;

	u = 0;
	if (i == 0)
		return (0);
	i--;
	while (i != 0)
	{
		if (str[i] != ' ' && str[i] != '\t')
			u = -1;
		i--;
	}
	return(u);
}

int		strlen_pathcmd(t_sdata *t_sdata, char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == '$' && ( i == 0 || str[i - 1] != '\\'))
		{
			// printf("\n\n HERRE >> %s", get_env_var_from_name(t_sdata->env_lst, str_x(str + i + 1)));
			if(get_env_var_from_name(t_sdata->env_lst, str_x(str + i + 1)) == NULL)
				return(-1);
			count += len(get_env_var_from_name(t_sdata->env_lst, str_x(str + i + 1)));
			i += len_x(str + i, ' ') - 1;
		}
		else
			count++;
		i++;
	}
	return (count);
}