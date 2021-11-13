/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo <jo@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:17:46 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/13 16:12:11 by jo               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fill_file_rdr(char *cmd, int nb, int type, char *file)
{
	int		i;
	t_redir	rdr;

	i = 0;
	rdr = initrdr();
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if ((cmd[i] == '<' && cmd[i + 1] == '<') && ++i > -1
			&& ++rdr.nb_redir_hdoc == nb && type == 4)
			return (get_file_redir(cmd + i + 2, file));
		else if ((cmd[i] == '>' && cmd[i + 1] == '>') && ++i > -1
			&& ++rdr.nb_redir_app == nb && type == 3)
			return (get_file_redir(cmd + i + 2, file));
		else if (cmd[i] == '<' && ++rdr.nro == nb && type == 2)
			return (get_file_redir(cmd + i + 1, file));
		else if (cmd[i] == '>' && ++rdr.nri == nb && type == 1)
			return (get_file_redir(cmd + i + 1, file));
		i++;
	}
	return (NULL);
}

int	find_size_rdr(char *cmd, int nb, int type)
{
	int		i;
	t_redir	rdr;

	i = 0;
	rdr = initrdr();
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if ((cmd[i] == '<' && cmd[i + 1] == '<') && ++i > -1
			&& ++rdr.nb_redir_hdoc == nb && type == 4)
			return (find_lenght_file(cmd + i + 2));
		else if ((cmd[i] == '>' && cmd[i + 1] == '>') && ++i > -1
			&& ++rdr.nb_redir_app == nb && type == 3)
			return (find_lenght_file(cmd + i + 2));
		else if (cmd[i] == '<' && ++rdr.nro == nb && type == 2)
			return (find_lenght_file(cmd + i + 1));
		else if (cmd[i] == '>' && ++rdr.nri == nb && type == 1)
			return (find_lenght_file(cmd + i + 1));
		i++;
	}
	return (0);
}

t_len_file	skip_qu_len(char *cmd, t_len_file fi)
{
	if (cmd[fi.i] == '\"')
	{
		fi.i++;
		while (cmd[fi.i] != '\"' && cmd[fi.i])
		{
			fi.size++;
			fi.i++;
		}
		if (cmd[fi.i])
			fi.i++;
	}
	else if (cmd[fi.i] == '\'')
	{
		fi.i++;
		while (cmd[fi.i] != '\'' && cmd[fi.i])
		{
			fi.size++;
			fi.i++;
		}
		if (cmd[fi.i])
			fi.i++;
	}
	return (fi);
}

int	find_lenght_file(char *cmd)
{
	t_len_file	fi;
	int			j;

	fi.size = 0;
	fi.i = 0;
	fi.i = skip_blank(cmd);
	while (cmd[fi.i])
	{
		j = fi.i;
		fi = skip_qu_len(cmd, fi);
		if ((cmd[fi.i] == ' ' || cmd[fi.i] == '\t'
				|| cmd[fi.i] == '<' || cmd[fi.i] == '>') && fi.i == j)
			return (fi.size);
		else if (fi.i == j)
		{
			fi.size++;
			fi.i++;
		}
	}
	return (fi.i);
}
