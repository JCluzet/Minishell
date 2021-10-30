/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:17:46 by jcluzet           #+#    #+#             */
/*   Updated: 2021/10/30 02:02:32 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	malloc_and_stock_redir(t_cmd_lst *cmds, char *cmd)
{
	char	**tab;
	t_redir	rdr;

	cmds->rdr = &rdr;
	rdr = get_size_redir(cmds, cmd);
	cmds->redir_ins = malloc_redir_next(cmd, rdr.nb_redir_in, 1);
	cmds->redir_outs = malloc_redir_next(cmd, rdr.nb_redir_out, 2);
	cmds->reddir_append = malloc_redir_next(cmd, rdr.nb_redir_app, 3);
	cmds->reddir_heredoc = malloc_redir_next(cmd, rdr.nb_redir_hdoc, 4);
	return(0);
}

char	**malloc_redir_next(char *cmd, int size, int type)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		tab[i] = malloc(sizeof(char) * find_size_rdr(cmd, i+1, type) + 1);
		tab[i] = fill_file_rdr(cmd, i+1, type, tab[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char		*fill_file_rdr(char *cmd, int nb, int type, char *file)
{
	int i;

	i = 0;
	t_redir	rdr;
	rdr = initrdr();
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			rdr.nb_redir_hdoc++;
			if (type == 4 && rdr.nb_redir_hdoc == nb)
				return (get_file_redir(cmd + i + 2, file));
			i++;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
		{
			rdr.nb_redir_app++;
			if (type == 3 && rdr.nb_redir_app == nb)
				return (get_file_redir(cmd + i + 2, file));
			i++;
		}
		else if (cmd[i] == '<')
		{
			rdr.nb_redir_out++;
			if (type == 2 && rdr.nb_redir_out == nb)
				return (get_file_redir(cmd + i + 1, file));
		}
		else if (cmd[i] == '>')
		{
			rdr.nb_redir_in++;
			if (type == 1 && rdr.nb_redir_in == nb)
				return (get_file_redir(cmd + i + 1, file));
		}
		i++;
	}
	return NULL;
}

int		find_size_rdr(char *cmd, int nb, int type) // retourne la taille du files apres le redir
{
	int i;

	i = 0;
	t_redir	rdr;
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
	return(0);
}

int		find_lenght_file(char *cmd)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	// printf("\ncmd = |%s|\n", cmd);
	i = skip_blank(cmd);
	while ((cmd[i+size] != ' ' && cmd[i+size] != '\t') && cmd[i+size])
		size++;
	return (size);
}

t_redir		get_size_redir(t_cmd_lst *cmds, char *cmd)
{
	int i;
	t_redir rdr;

	rdr = initrdr();
	i = 0;
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			rdr.nb_redir_hdoc++;
			i++;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
		{
			rdr.nb_redir_app++;
			i++;
		}
		else if (cmd[i] == '<')
			rdr.nb_redir_out++;
		else if (cmd[i] == '>')
			rdr.nb_redir_in++;
		i++;
	}
	return (rdr);
}

t_redir	initrdr(void)
{
	t_redir rdr;

	rdr.nb_redir_in = 0;
	rdr.nb_redir_out = 0;
	rdr.nb_redir_app = 0;
	rdr.nb_redir_hdoc = 0;
	return (rdr);
}
