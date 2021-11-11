/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:17:46 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/11 23:50:09 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_rdr_of_f(t_fin *f)
{
	if (f->cmd[f->i] == '<' && f->cmd[f->i + 1] == '<')
	{
		f->rdr.nb_redir_hdoc++;
		if (f->type == 4 && f->rdr.nb_redir_hdoc == f->nb)
			return (2);
		f->i++;
	}
	else if (f->cmd[f->i] == '>' && f->cmd[f->i + 1] == '>')
	{
		f->rdr.nb_redir_app++;
		if (f->type == 3 && f->rdr.nb_redir_app == f->nb)
			return (2);
		f->i++;
	}
	else if (f->cmd[f->i] == '<' || f->cmd[f->i] == '>')
	{
		if (f->cmd[f->i] == '<')
			f->rdr.nro++;
		if (f->cmd[f->i] == '<')
			f->rdr.nri++;
		if ((f->type == 2 && f->rdr.nro == f->nb && f->cmd[f->i] == '<')
			|| (f->type == 1 && f->rdr.nri == f->nb && f->cmd[f->i] == '>'))
			return (1);
	}
	return (0);
}

char	*fill_file_rdr(char *cmd, int nb, int type, char *file)
{
	t_fin	f;

	f.i = 0;
	f.rdr = initrdr();
	f.cmd = cmd;
	f.nb = nb;
	f.type = type;
	f.file = file;
	while (f.cmd[f.i])
	{
		f.i = find_quotes(f.cmd, f.i, f.cmd[f.i]);
		f.n = get_rdr_of_f(&f);
		if (f.n == 1)
			return (get_file_redir(f.cmd + f.i + 1, f.file));
		if (f.n == 2)
			return (get_file_redir(f.cmd + f.i + 2, f.file));
		f.i++;
	}
	return (NULL);
}

int	find_size_rdr(char *cmd, int nb, int type)
{
	t_fin	f;

	f.i = 0;
	f.rdr = initrdr();
	f.cmd = cmd;
	f.nb = nb;
	f.type = type;
	while (f.cmd[f.i])
	{
		f.i = find_quotes(f.cmd, f.i, f.cmd[f.i]);
		f.n = get_rdr_of_f(&f);
		if (f.n)
			return (find_lenght_file(f.cmd + f.i + f.n));
		f.i++;
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
