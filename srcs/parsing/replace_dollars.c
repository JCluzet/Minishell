/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 02:05:18 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/05 22:13:08 by jcluzet          ###   ########.fr       */
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

int		len_doll_null(char const *str)
{
	int				i;
	
	i = 1;
	while (str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i] != '$')
		++i;
    // printf("dollh >> %d\n", i-1);
	return (i - 1);
}

int		strlen_pathcmd(t_sdata *t_sdata, char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	printf("str_start >> |%s|", str);
	while(str[i] != '\0')
	{
		i = find_quotes(str, i, str[i]);
		if (str[i] == '$')
		{
			if (get_env_var_from_name(t_sdata->env_lst, str_x(str + i + 1)) == NULL)
			{
				count++;
				i += len_doll_null(str + i);
			}
			else
			{
				count += len(get_env_var_from_name(t_sdata->env_lst, str_x(str + i + 1)));
				i += len_doll(str + i) - 1;
			}
		}
		else
			count++;
		printf("\nstr >> |%s| et I est a |%d|\n", str, i);
		i++;
	}
	printf("str_end >> |%s|\n\n", str);
	//printf("\nACTUEL RETURN DE STRLEN >> |%d|\n", count);
	return (count);
}

char 	*replace_dollars(char *old_cmd, t_sdata *sdata)
{
    int i;
    int u;
    int j;
    char *newcmd;
    char *tmp;

    i = 0;
    j = 0;
    u = 0;
	// printf("\nstr0 >> |%s|\n", old_cmd);
	strlen_pathcmd(sdata, old_cmd);
	
    // newcmd = malloc(sizeof(char) * (strlen_pathcmd(sdata, old_cmd)));

	// printf("\nstr1 >> |%s|\n", old_cmd);
    // printf("\n\nHere is the new_cmd strlen > |%d|", strlen_pathcmd(sdata, old_cmd));
    // while (i < strlen_pathcmd(sdata, old_cmd) - 1)
    // {
    //     i = find_quotes(old_cmd, i, old_cmd[i]);
    //     if (old_cmd[i] == '$')
    //     {
    //         if (get_env_var_from_name(sdata->env_lst, str_x(old_cmd + i + 1)) == NULL)
    //         {
    //             newcmd[j] = ' ';
    //             j++;
	// 			i += len_doll_null(old_cmd + i) - 1;
    //         }
    //         else
    //         {
    //             tmp = get_env_var_from_name(sdata->env_lst, str_x(old_cmd + i + 1));
    //             while (tmp[u])
    //             {
 	// 			    newcmd[j] = tmp[u];
 	// 			    j++;
 	// 			    u++;
 	// 		    }
 	// 		    u = 0;
 	// 		    i += len_doll(old_cmd + i) - 1;
    //         }
    //     }
    //     else
    //     {
 	// 		newcmd[j] = old_cmd[i];
 	// 		j++;
 	// 	}
    //     i++;
    // }
    // newcmd[j] = '\0';
	return(old_cmd);
    printf("\n\n\nYO CMD IS HERE |%s|", newcmd);
    return(newcmd);
}