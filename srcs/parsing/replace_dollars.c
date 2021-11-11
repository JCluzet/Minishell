/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 02:05:18 by jcluzet           #+#    #+#             */
/*   Updated: 2021/11/11 17:11:38 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_path	strl_doll(t_path pa, t_sdata *t_sdata, char *str)
{
	pa.i++;
	pa.tmpvar = str_find_var(str + pa.i);
	pa.tmp = get_env_var_from_name(t_sdata->env_lst, pa.tmpvar);
	free(pa.tmpvar);
	if (pa.tmp == NULL)
		pa.i += skip_var(str + pa.i);
	else
	{
		pa.count += len(pa.tmp);
		pa.i += skip_var(str + pa.i);
	}
	return (pa);
}

int	strlen_pathcmd(t_sdata *t_sdata, char *str)
{
	t_path	pa;

	pa.i = 0;
	pa.count = 0;
	while (str[pa.i])
	{
		if (str[pa.i] == '$' && (str[pa.i + 1] == '?')
			&& is_insquote(str, pa.i))
		{
			pa.i += 2;
			pa.count += int_len(t_sdata->lrval);
		}
		else if (str[pa.i] == '$' && is_in_set(str[pa.i + 1],
				ENV_CHAR_LIST) && is_insquote(str, pa.i))
			pa = strl_doll(pa, t_sdata, str);
		else if (str[pa.i])
		{
			pa.i++;
			pa.count++;
		}
	}
	return (pa.count);
}

t_doll	replace_var_doll(t_sdata *sdata, char *old_cmd, t_doll dol)
{
	dol.i++;
	dol.tmpvar = str_find_var(old_cmd + dol.i);
	dol.tmp = get_env_var_from_name(sdata->env_lst, dol.tmpvar);
	free(dol.tmpvar);
	if (dol.tmp == NULL)
		dol.i += skip_var(old_cmd + dol.i);
	else
	{
		while (dol.tmp[dol.j])
		{
			dol.newcmd[dol.count] = dol.tmp[dol.j];
			dol.j++;
			dol.count++;
		}
		dol.i += skip_var(old_cmd + dol.i);
		dol.j = 0;
	}
	return (dol);
}

t_doll	replace_var_mark(t_sdata *sdata, t_doll dol)
{
	dol.i += 2;
	dol.newcmd = put_int_str(int_len(sdata->lrval), dol.newcmd,
			dol.count, sdata->lrval);
	dol.count += int_len(sdata->lrval);
	return (dol);
}

char	*replace_dollars(char *old_cmd, t_sdata *sdata)
{
	t_doll	dol;

	dol.j = 0;
	dol.i = 0;
	dol.count = 0;
	dol.newcmd = malloc(sizeof(char) * (strlen_pathcmd(sdata, old_cmd) + 1));
	if (!dol.newcmd)
		return (NULL);
	while (old_cmd[dol.i])
	{
		if (old_cmd[dol.i] == '$' && (old_cmd[dol.i + 1] == '?')
			&& is_insquote(old_cmd, dol.i))
			dol = replace_var_mark(sdata, dol);
		else if (old_cmd[dol.i] == '$' && is_in_set(old_cmd[dol.i + 1],
				ENV_CHAR_LIST) && is_insquote(old_cmd, dol.i))
			dol = replace_var_doll(sdata, old_cmd, dol);
		else if (old_cmd[dol.i])
		{
			dol.newcmd[dol.count] = old_cmd[dol.i];
			dol.i++;
			dol.count++;
		}
	}
	dol.newcmd[dol.count] = '\0';
	return (dol.newcmd);
}
