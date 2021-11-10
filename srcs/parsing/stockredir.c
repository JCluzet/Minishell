/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stockredir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 00:06:32 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/11 00:03:22 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	malloc_and_stock_redir(t_cmd_lst *c, char *cmd)
{
	c->last_rdr = initrdr2();
	get_size_redir(c, cmd); // nickel
	c->redir_ins = malloc_redir_next(c, cmd, c->rdr->nb_redir_in, 1);
	c->redir_outs = malloc_redir_next(c, cmd, c->rdr->nb_redir_out, 2);
	c->reddir_append = malloc_redir_next(c, cmd, c->rdr->nb_redir_app, 3);
	c->reddir_heredoc = malloc_redir_next(c, cmd, c->rdr->nb_redir_hdoc, 4);
	return (0);
}

char	**malloc_redir_next(t_cmd_lst *cmds, char *cmd, int size, int type)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * (size + 1)); // malloc le nombre de redir pour 1 type de redir 
	while (i < size)
	{
		tab[i] = malloc(sizeof(char) * (find_size_rdr(cmd, i + 1, type) + 1));
		tab[i] = fill_file_rdr(cmd, i + 1, type, tab[i]);
		
		cmds->rdr_nb++;
		if (type == 1)
			cmds->rdr->nb_redir_in = cmds->rdr_nb;
		else if (type == 2)
			cmds->rdr->nb_redir_out = cmds->rdr_nb;
		else if (type == 3)
			cmds->rdr->nb_redir_app = cmds->rdr_nb;
		else
			cmds->rdr->nb_redir_hdoc = cmds->rdr_nb;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

t_redir	initrdr(void)
{
	t_redir	rdr;

	rdr.nb_redir_in = 0;
	rdr.nb_redir_out = 0;
	rdr.nb_redir_app = 0;
	rdr.nb_redir_hdoc = 0;
	return (rdr);
}

t_redir	*initrdr2(void)
{
	t_redir	*rdr;

	rdr = malloc(sizeof(t_redir));
	rdr->nb_redir_in = 0;
	rdr->nb_redir_out = 0;
	rdr->nb_redir_app = 0;
	rdr->nb_redir_hdoc = 0;
	return (rdr);
}

// char	*rmv_rdr_from_cmd(char *cmd)
// {
// 	return (ft_substr(cmd + end_first_rdr(cmd), 0 , get_last_rdr_idx(cmd + end_first_rdr(cmd))));
// }

// remove all >> and << from cmd with her file name and return the new cmd

int		strlen_cmd_without_rdr(char *cmd)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			i++;
			if (cmd[i] == '<' || cmd[i] == '>')
				i++;
			// printf("I1>|%d|", i);
			i += skip_blank(cmd + i);
			// printf("I2>|%d|", i);
			while ((duoquote(cmd, i) || (cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '<' && cmd[i] != '>')) && cmd[i])
				i++;
		}
		else
		{
			count++;
		}
		if (cmd[i])
			i++;
	}
	return (count);
}

int		strlen_cmd_without_quotes(char *cmd)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while(cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
			{
				count++;
				i++;
			}
			i++;
		}
		else if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
			{
				count++;
				i++;
			}
			i++;
		}
		else
		{
			if (cmd[i])
				i++;
			count++;
		}
	}
	return (count);
}


char	*rmv_quotes_from_cmd(char *cmd)
{
	int i;
	int count;
	char *newcmd;

	count = 0;
	i = 0;
	//printf("\nOLDCMD > |%s|", cmd);
	newcmd = malloc(sizeof(char *) * (strlen_cmd_without_quotes(cmd) + 1));
	while(cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
			{
				newcmd[count] = cmd[i];
				count++;
				i++;
			}
			i++;
		}
		else if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
			{
				newcmd[count] = cmd[i];
				count++;
				i++;
			}
			i++;
		}
		else 
		{
			newcmd[count] = cmd[i];
			count++;
			if (cmd[i])
				i++;
		}
	}
	newcmd[count] = '\0';
	free(cmd);
	//printf("\nNEWCMD > |%s|", newcmd);
	return(newcmd);
}

char	*rmv_rdr_from_cmd(char *cmd)
{
	int i;
	int count;
	char *newcmd;

	count = 0;
	i = 0;
	// printf("\nOLDCMD > |%s|", cmd);
	newcmd = malloc(sizeof(char *) * (strlen_cmd_without_rdr(cmd) + 1));
	while (cmd[i])
	{
		if ((cmd[i] == '<' || cmd[i] == '>') && !duoquote(cmd, i))
		{
			i++;
			if (cmd[i] == '<' || cmd[i] == '>')
				i++;
			i += skip_blank(cmd + i);
			while ((duoquote(cmd, i) || (cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '<' && cmd[i] != '>')) && cmd[i])
				i++;
		}
		else
		{
			newcmd[count] = cmd[i];
			count++;
		}
		if (cmd[i])
			i++;
	}
	newcmd[count] = '\0';
	free(cmd);
	// printf("\nNEWCMD > |%s|", newcmd);
	return(newcmd);
}