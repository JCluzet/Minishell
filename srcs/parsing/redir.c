/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:17:46 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/10 00:10:24 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*fill_file_rdr(char *cmd, int nb, int type, char *file)
{
	int i;
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

int		find_size_rdr(char *cmd, int nb, int type)
{
	int i;
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

int		find_lenght_file(char *cmd)
{
	int i;
	int size;
	int dquote = -1;
	int squote = -1;

	size = 0;
	i = 0;
	//printf("\ncmd uno >> |%s|", cmd);
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
		else if (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '<' || cmd[i] == '>')
		{
			//printf("\ncmd deuxio >> |%s|", cmd);
			return(size);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (i);
}

void get_size_redir(t_cmd_lst *cmds, char *cmd)
{
	int	i;

	cmds->rdr = initrdr2();
	cmds->type_last_rdr_in = 0;
	cmds->type_last_rdr_out = 0;
	i = 0;
	//printf("\ncmd YOLGDFGLD >> |%s|", cmd);
	while (cmd[i])
	{
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			cmds->type_last_rdr_in = 2;
			cmds->rdr->nb_redir_hdoc++;
			i++;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
		{
			cmds->type_last_rdr_out = 2;
			cmds->rdr->nb_redir_app++;
			i++;
		}
		else if (cmd[i] == '<')
		{
			cmds->rdr->nb_redir_out++;
			cmds->type_last_rdr_in = 1;
		}
		else if (cmd[i] == '>')
		{
			cmds->rdr->nb_redir_in++;
			cmds->type_last_rdr_out = 1;
		}
		else
			i = find_quotes(cmd, i, cmd[i]);
		i++;
	}
}
