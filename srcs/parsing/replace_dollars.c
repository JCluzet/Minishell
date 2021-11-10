/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 02:05:18 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/10 23:57:17 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** replace dollars return cmd with $X changed by var name, or remove $X if there is no var
*/

char 	*str_find_var(char *str) // recoit la chaine a partir de juste apres $
{
	int i;
	char *tmp;
	
	i = 0;
	// printf("\nbegin of str_find_var |%s|", str);
	while(str[i])
	{
		if (!is_in_set(str[i], ENV_CHAR_LIST))
			break ;
		i++;
	}
	if (i == 0)
		return (NULL);
	tmp = malloc(sizeof(char *) * (i + 1));
	return (ft_strncpy(tmp, str, i));
}

int 	skip_var(char *str) // recoit la chaine a partir de juste apres $
{
	int i;
	
	i = 0;
	while(str[i])
	{
		if (!is_in_set(str[i], ENV_CHAR_LIST))
			return (i);
		i++;
	}
	return(i);
}

int		int_len(int i)
{
	int count;

	count = 1;
	while (i > 9)
	{
		i = i / 10;
		count++;
	}
	return (count);
}

int		strlen_pathcmd(t_sdata *t_sdata, char *str)
{
	int i;
	int count;
	char *tmpvar;
	char *tmp;

	i = 0;
	count = 0;
	while(str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '?') && is_insquote(str, i))
		{
			i += 2;
			count += int_len(t_sdata->lrval);
		}
		else if (str[i] == '$' && is_in_set(str[i + 1], ENV_CHAR_LIST) && is_insquote(str, i))
		{
			i++;
			tmpvar = str_find_var(str + i);
			// printf("\ntmpvar |%s|", tmpvar);
			tmp = get_env_var_from_name(t_sdata->env_lst, tmpvar);
			free(tmpvar);
			if (tmp == NULL)
				i += skip_var(str + i);
			else
			{
				count += len(tmp);
				i += skip_var(str + i);
			}
		}
		else if (str[i])
		{
			i++;
			count++;
		}
	}
	// printf("\nHere is the strlen > |%d|", count);
	return (count);
}

char *put_int_str(int nb_len, char *cmd, int count, int lrval)
{
	printf("\n\nnb_len > %d\nlrval > %d\ncount > %d\n", nb_len, lrval, count);
	if (nb_len == 3)
	{
		cmd[count] = (lrval/100) + 48;
		cmd[count + 1] = ((lrval/10) % 10) + 48;
		cmd[count + 2] = (lrval % 10) + 48;
	}
	if (nb_len == 2)
	{
		cmd[count] = (lrval/10) + 48;
		cmd[count + 1] = (lrval % 10) + 48;
	}
	if (nb_len == 1)
		cmd[count] = lrval + 48;
	return (cmd);
}

// gerer le cas du $?
// gerer le cas du is_insquote > ne rien faire

char 	*replace_dollars(char *old_cmd, t_sdata *sdata)
{
    int i;
	int j;
    int count;
	char *newcmd;
	char *tmp;
	char *tmpvar;

	j = 0;
    i = 0;
    count = 0;
	//printf("\nodd_cmd |%s|", old_cmd);
    newcmd = malloc(sizeof(char) * (strlen_pathcmd(sdata, old_cmd) + 1));
	while(old_cmd[i])
	{
		if (old_cmd[i] == '$' && (old_cmd[i + 1] == '?') && is_insquote(old_cmd, i))
		{
			i += 2;
			newcmd = put_int_str(int_len(sdata->lrval), newcmd, count, sdata->lrval);
			count += int_len(sdata->lrval);
		}
		else if (old_cmd[i] == '$' && is_in_set(old_cmd[i + 1], ENV_CHAR_LIST) && is_insquote(old_cmd, i))
		{
			i++;
			tmpvar = str_find_var(old_cmd + i);
			// printf("\ntmpvar |%s|", tmpvar);
			tmp = get_env_var_from_name(sdata->env_lst, tmpvar);
			free(tmpvar);
			if (tmp == NULL)
				i += skip_var(old_cmd + i);
			else
			{
				while (tmp[j])
				{
					newcmd[count] = tmp[j];
					j++;
					count++;
				}
				i += skip_var(old_cmd + i);
				j = 0;
			}
		}
		else if (old_cmd[i])
		{
			newcmd[count] = old_cmd[i];
			i++;
			count++;
		}
	}
	newcmd[count] = '\0';
    //printf("\nnew_cmd |%s|", newcmd);
	// return (old_cmd);
	return (newcmd);
}