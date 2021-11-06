/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 02:05:18 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/06 01:05:53 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** replace dollars return cmd with $X changed by var name, or remove $X if there is no var
*/

int		len_doll(char const *str)
{
	int				i;
	
	i = 1;
	while (str[i] && (str[i] > 64) && (str[i] < 91))
		++i;

    //printf("doll >> %d", i);
	return (i);
}

int		len_doll_null(char *str)
{
	int				i;
	
	i = 1;
	while (str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i] != '$')
		++i;
    // printf("dollh >> %d\n", i-1);
	return (i - 1);
}

char 	*str_cmd(char *str)
{
	int i;
	int u;
	char *tmp;

	i = -1;
	u = 0;
	while(str[i])
	{
		i++;
		if (((str[i] == ' ' || str[i] == '<' || str[i] == '>' || str[i] == '$') && u == 0))
			u = i;
	}
	if (u == 0)
		u = i;
	tmp = malloc(sizeof(char *) * (i + 1));
	tmp = ft_strncpy(tmp, str, u);
	//printf("\nTMP >>%s\nSTR>> %s\nU>> %d", tmp, str, u);
	return (ft_strncpy(tmp, str, u));
}

int		strlen_pathcmd(t_sdata *t_sdata, char *str)
{
	int i;
	int count;
	char *tmp;

	count = 0;
	i = 0;
	//printf("str_start >> |%s|", str);
	while(str[i] != '\0')
	{
		i = find_quotes(str, i, str[i]);
		if (str[i] == '$')
		{
			tmp = get_env_var_from_name(t_sdata->env_lst, str_cmd(str + i + 1));
			if (tmp == NULL)
			{
				count++;
				i += len_doll_null(str + i);
			}
			else
			{
				count += len(tmp);
				i += len_doll(str + i) - 1;
			}
		}
		else
			count++;
		i++;
	}
	//printf("str_end >> |%s|", str);
	//printf("\nACTUEL RETURN DE STRLEN >> |%d|\n", count);
	return (count);
}

char 	*replace_dollars(char *old_cmd, t_sdata *sdata)
{
    int i;
    int count;
    int j;
    char *newcmd;
    char *tmp;

    i = 0;
    j = 0;
    count = 0;
	// printf("\nstr0 >> |%s|\n", old_cmd);
	// strlen_pathcmd(sdata, old_cmd);
	
    newcmd = malloc(sizeof(char) * (strlen_pathcmd(sdata, old_cmd) + 1));

	// printf("\nstr1 >> |%s|\n", old_cmd);
    // printf("\n\nHere is the new_cmd strlen > |%d|", strlen_pathcmd(sdata, old_cmd));

	while(old_cmd[i] != '\0')
	{
		i = find_quotes(old_cmd, i, old_cmd[i]);
		if (old_cmd[i] == '$')
		{
			tmp = get_env_var_from_name(sdata->env_lst, str_cmd(old_cmd + i + 1));
			if (tmp == NULL)
			{
				newcmd[count] = ' ';
				count++;
				i += len_doll_null(old_cmd + i);
			}
			else
			{
				while (tmp[j])
                {
 				    newcmd[count] = tmp[j];
 				    j++;
 				    count++;
 			    }
 			    j = 0;
				i += len_doll(old_cmd + i) - 1;
			}
		}
		else
		{
			newcmd[count] =  old_cmd[i];
			count++;
		}
		i++;
	}
	newcmd[count] = '\0';
    //printf("\nYO CMD IS HERE |%s|", newcmd);
	free(old_cmd);
	return(newcmd);
}