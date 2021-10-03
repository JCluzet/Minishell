/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo <jo@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:08:47 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/03 02:17:29 by jo               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void (*builtins[7])(t_sdata *) = {display_env, shell_export, shell_unset, pwd,
	echo , shell_cd, shell_exit};

static const char *g_builtins_mask[7] = {"env", "export", "unset", "pwd", "echo", "cd", "exit"};


int	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return(-1);
	while (i < 7)
	{
		if (!ft_strncmp(g_builtins_mask[i], cmd, len(g_builtins_mask[i])))
			return (i);
		++i;
	}
	if (i == 7)
		return (-1);
	return (i);
}

char	*find_cmd_path(t_cmd_lst *cmd, char **paths)
{
	int		i;
	char	*path;
	int		fd;

	i = 0;
	if (!cmd)
		return (NULL);
	while (paths[i])
	{
		if (cmd->cmd[0] != '/')
			path = cncat(cncat(paths[i], "/", 0, 0), cmd->cmd, 0, 0);
		else
			path = ft_strdup_free(cmd->cmd, 0);
		fd = open(path, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			return (path);
		}
		free(path);
		++i;
	}
	return (NULL);
}

t_cmd_lst		*parse_line(t_sdata *sdata, char *line)
{
	t_cmd_lst *cmd;
	int i;

	i = 0;
	if (quotes_check(line) == -1 || !line)
		return(NULL);
	if (pipe_check(line) == -1)
	{
		printf("minishell: parse error near '|'\n");
		return (NULL);
	}
	// replace_dollars(line, sdata);
	cmd = split_cmds(line);
	printf_linked_list(cmd);
	// cmd = fill_cmds(line);
	while (i < nb_of_cmds(line))
	{
		if (cmd->builtin_idx > 6 || cmd->builtin_idx == -1) // parse toutes les cmds
			cmd->cmd_path = is_cmd_executable(cmd->cmd, sdata);
		if (cmd->next != NULL)
			cmd = cmd->next;
	i++;
	}
	return (cmd);
}

int		pipe_check(char *str)
{
	int i;
	int blank;

	blank = -1;
	i = 0;
	while(str[i])
	{
		if (str[i] == '|')
		{
			if (i == len(str) - 1)
				return (-1);
			if (i == 0)
				return (-1);
			if (blank == -1)
				return (-1);
			blank = -1;
		}
		if (str[i] != ' ' && str[i] != '\t')
			blank = 0;
		i++;
	}
	return(0);
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

char 	*replace_dollars(char *str, t_sdata *sdata)
{
	int i;
	char *newcmd;
	char *tmp;
	int card;
	int j;
	int u;

	u = 0;
	j = 0;
	i = 0;
	card = strlen_pathcmd(sdata, str);
	if (card == -1)
		return (NULL);
	newcmd = malloc(sizeof(char) * (card + 1));
	//printf("\n\nMalloc de %d\n", card);
	while (j < card)
	{
		if (str[i] == '$' && ( i == 0 || (str[i-1] != '\\') ))
		{
			tmp = get_env_var_from_name(sdata->env_lst, str_x(str + i + 1));
			while (tmp[u])
			{
				newcmd[j] = tmp[u];
				j++;
				u++;
			}
			u = 0;
			i += len_x(str + i, ' ') - 1;
		}
		else
		{
			newcmd[j] = str[i];
			j++;
		}
		i++;
	}
	newcmd[j] = '\0';
	//printf("\n\n>>%s<<\n", newcmd);
	return(newcmd);
}

int		quotes_check(char *str)
{
	t_quote qt;
	qt.double_q = 0;
	qt.simple_q = 0;
	int i;
	

	i = 0;
	while (str[i])
	{
		checkquotes(str[i], &qt);
		i++;
	}
	if (qt.simple_q % 2 != 0)
	{
		printf("minishell: unexpected EOF while looking for matching '\''\n");
		return(-1);
	}
	if (qt.double_q % 2 != 0)
	{
		printf("minishell: unexpected EOF while looking for matching '\"'\n");
		return(-1);
	}
	return(0);
}	

int		checkquotes(char c, t_quote *qt)
{
	if (c == '\"')
	{
		if (qt->simple_q % 2 == 0)
			qt->double_q++;
		else
			qt->double_q_insimple++;
	}
	if (c == '\'')
	{
		if (qt->double_q % 2 == 0)	
			qt->simple_q++;
		else
			qt->simple_q_indouble++;
	}
	return(0);
}

int		check_error(t_cmd_lst *cmds)
{
	if (!cmds)
		return(-1);
	if ((((cmds->builtin_idx > 6) && !cmds->cmd_path) || (cmds->builtin_idx == -1 && !cmds->cmd_path)) && cmds->argv)
	{
		write(1, "minishell: command not found: ", 31);
		write(1, cmds->cmd, len(cmds->cmd));
		write(1, "\n", 1);
	}
	return(0);
}
