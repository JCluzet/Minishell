/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_str_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:03:57 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/10 18:51:04 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_x(char const *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

char*	get_file_redir(char *cmd, char *file)
{
	int i;
	int size;

	size = 0;
	i = 0;
	printf("\ncmdf >>|%s|\n", cmd);
	i = skip_blank(cmd);
	// while ((duoquote(cmd, i+size) || (cmd[i+size] != ' ' && cmd[i+size] != '\t' && cmd[i+size] != '<' && cmd[i+size] != '>')) && cmd[i+size])
	// {
	// 	file[size] = cmd[size + i];
	// 	size++;
	// }
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"' && cmd[i])
			{
				file[size] = cmd[i];
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
				file[size] = cmd[i];
				size++;
				i++;
			}
			if (cmd[i])
				i++;
		}
		else if (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '<' || cmd[i] == '>')
		{
			//printf("\ncmd deuxio >> |%s|", cmd);
			file[size] = '\0';
			return(file);
		}
		else
		{
			file[size] = cmd[i];
			size++;
			i++;
		}
	}
	file[size] = '\0';
	printf("\nfile >>|%s|\n", file);
	if (size == 0)
		file = NULL;
	return (file);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

void	putstr_err(char *str)
{
	if (!str)
		return ;
	write(2, str, len(str));
}

int	is_maj(char c)
{
	if ((c > 64) && (c < 91))
		return (1);
	if ((c > 96) && (c < 123))
		return (1);
	return (0);
}
