/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo <jo@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:17:46 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/13 15:50:21 by jo               ###   ########.fr       */
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
			rdr.nro++;
			if (type == 2 && rdr.nro == nb)
				return (get_file_redir(cmd + i + 1, file));
		}
		else if (cmd[i] == '>')
		{
			rdr.nri++;
			if (type == 1 && rdr.nri == nb)
				return (get_file_redir(cmd + i + 1, file));
		}
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
			rdr.nro++;
			if (type == 2 && rdr.nro == nb)
				return (find_lenght_file(cmd + i + 1));
		}
		else if (cmd[i] == '>')
		{
			rdr.nri++;
			if (type == 1 && rdr.nri == nb)
				return (find_lenght_file(cmd + i + 1));
		}
		i++;
	}
	return (0);
}

int	find_lenght_file(char *cmd)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	i = skip_blank(cmd);
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"' && cmd[i])
			{
				size++;
				i++;
			}
			if (cmd[i])
				i++;
		}
		else if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'' && cmd[i])
			{
				size++;
				i++;
			}
			if (cmd[i])
				i++;
		}
		else if (cmd[i] == ' ' || cmd[i] == '\t'
			|| cmd[i] == '<' || cmd[i] == '>')
		{
			return (size);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (i);
}
