/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:48:31 by ambelkac          #+#    #+#             */
/*   Updated: 2021/08/10 14:50:06 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	lennewline(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		++i;
	}
	return (0);
}

int	read_fd(int fd, char **str)
{
	char			*buffer;
	int				i;
	int				red;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	i = 0;
	while (i < BUFFER_SIZE + 1)
		buffer[i++] = '\0';
	i = 0;
	red = read(fd, buffer, BUFFER_SIZE);
	while (red > 0)
	{
		*str = (cncat(*str, buffer, 1, 0));
		while (i < BUFFER_SIZE + 1)
			buffer[i++] = '\0';
		i = 0;
		if (red != BUFFER_SIZE || lennewline(*str) || (*str)[0] == '\n')
			break ;
		red = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (red);
}

int	is_there_save(char **str, char **save)
{
	if (!*save)
		return (0);
	if (!lennewline(*save) && (*save)[0] != '\n')
	{
		*str = cncat(*str, *save, 1, 1);
		*save = NULL;
		return (0);
	}
	if (lennewline(*save) || (*save)[0] == '\n')
	{
		*str = cncat(*str, ft_substr_free(*save,
					0, lennewline(*save), 0), 1, 1);
		*save = ft_substr_free(*save,
				lennewline(*save) + 1, len(*save) - lennewline(*save), 1);
		if (*save && (*save)[0] == '\0')
		{
			free(*save);
			*save = NULL;
		}
	}
	return (1);
}

int	cut_line(char **save, char **str)
{
	if (!lennewline(*str) && *str[0] != '\n')
		return (0);
	*save = cncat(*save, ft_substr_free(*str,
				lennewline(*str) + 1, len(*str) - lennewline(*str), 0), 1, 1);
	*str = ft_substr_free(*str, 0, lennewline(*str), 1);
	if (*save && (*save)[0] == '\0')
	{
		free(*save);
		*save = NULL;
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char		*save = NULL;
	int				read_val;
	int				save_val;
	char			*str;

	str = NULL;
	save_val = is_there_save(&str, &save);
	if (save_val)
	{
		*line = str;
		return (1);
	}
	read_val = read_fd(fd, &str);
	if (read_val == -1)
		return (-1);
	if (str == NULL)
	{
		*line = ft_strdup_free("\0", 0);
		return (0);
	}
	save_val = cut_line(&save, &str);
	*line = str;
	if ((!read_val && !save) || !save_val)
		return (0);
	return (1);
}
