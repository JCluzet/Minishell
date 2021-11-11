/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:17:46 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/11 17:39:23 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	grate_ligne(t_fin *f)
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
			f->rdr.nb_redir_out++;
		if (f->cmd[f->i] == '<')
			f->rdr.nb_redir_in++;
		if ((f->type == 2 && f->rdr.nb_redir_out == f->nb && f->cmd[f->i] == '<')
		|| (f->type == 1 && f->rdr.nb_redir_in == f->nb && f->cmd[f->i] == '>'))
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
		f.n = grate_ligne(&f);
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
	int		i;
	t_redir	rdr;

	i = 0;
	rdr = initrdr();
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			rdr.nb_redir_hdoc++;
			if (type == 4 && rdr.nb_redir_hdoc == nb)
				return (find_lenght_file(cmd + i + 2));
			i++;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
		{
			rdr.nb_redir_app++;
			if (type == 3 && rdr.nb_redir_app == nb)
				return (find_lenght_file(cmd + i + 2));
			i++;
		}
		else if (cmd[i] == '<')
		{
			rdr.nb_redir_out++;
			if (type == 2 && rdr.nb_redir_out == nb)
				return (find_lenght_file(cmd + i + 1));
		}
		else if (cmd[i] == '>')
		{
			rdr.nb_redir_in++;
			if (type == 1 && rdr.nb_redir_in == nb)
				return (find_lenght_file(cmd + i + 1));
		}
		i++;
	}
	return (0);
}

int	find_lenghtwq(char *cmd)
{
	int	i;
	int	size;
	int	temp;

	size = 0;
	i = skip_blank(cmd);
	while (cmd[i])
	{
		temp = i;
		i = skip_quotes_arg(cmd, i);
		if (temp == i && (cmd[i] == ' ' || cmd[i] == '\t'
				|| cmd[i] == '<' || cmd[i] == '>'))
			return (i);
		else if (temp == i)
			i++;
	}
	return (i);
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
