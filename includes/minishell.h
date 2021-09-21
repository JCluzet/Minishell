/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:27:14 by ambelkac          #+#    #+#             */
/*   Updated: 2021/09/21 00:15:44 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
# include <sys/wait.h>

# define FIRST_ENV_CHAR_LIST "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
# define ENV_CHAR_LIST "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_="
# define BUFFER_SIZE 4096

typedef struct	s_command_list
{

	char		*cmd;//		trimmed cmd name                                     >> nom de la commande tapé
	char		**argv;//	Null terminated arg of cmd                           >> arguments que prennent la commande ou NULL si sans argument
	char		*cmd_path;// Valid bath to executable file, set to NULL if none  >> path vers l'executable (si existant)
	int			builtin_idx; // if > 7 is a builtin, if == 7 is not              >> le numero du builtin ( 7 si non existant )
	char		redir; //-2 - '<<' | -1 - '<' | 0 none | 1 - '>' | 2 - '>>'      >> une eventuel redirection trouvé apres la commande
	int			fdi;//	fd of infile, set to -1 if no reddir, dup with stdin
	int			fdo;//	fd of outfile, set to -1 if no reddir, dup with stdout
	char		*reff_arg;//	$ refference arguments are stored here
	// struct s_command_list	*next;
}				t_cmd_lst;

typedef struct s_environement_list
{
	char	*name;
	char 	*var;
	struct s_environement_list	*next;
}				t_env_lst;

typedef struct	s_shell_data                   // structure envoyé a chaque fonction
{
	t_cmd_lst	*cmds;//	Linked list of every cmd waiting for execution
	char		**env;
	t_env_lst	*env_lst;
	char		**bin_paths;//	Path to all binary folder from ENV
	char		lrval;// Last return value of launched cmd
}				t_sdata;


// Testing

void	print_cmds(t_cmd_lst *cmds, char *cmd, int v);

//		Main
//	shell_loop.c
int	shell_loop(t_sdata *sdata);

//		Parsing
//	parse_line
t_cmd_lst	*parse_line(t_sdata *sdata, char *line);
int		check_error(t_cmd_lst *cmd);
int	is_builtin(char *cmd);
//	fill_cmds.c
void	fill_cmds(t_cmd_lst *cmds, char *cmd);
t_cmd_lst	*fill_multi_cmds(char *cmd);
//		Execution
//	dispatcher
void	execution_dispatcher(t_sdata *sdata);

//		Environement
//	env_parsing.c
char	*get_env_var_from_name(t_env_lst *list, char *name);
int	does_env_var_exist(t_env_lst *env, char *var);
char	*get_env_var_name_from_arg(char *arg);
int	is_env_var_valid(char *arg);
int	get_idx_var_in_env(char **env, char *var);
char	*get_var_in_env(char **env, char *var);

//		Builtins
//	env.c
void	display_env(t_sdata *sdata);
//	unset.c
void	shell_unset(t_sdata *sdata);
//	export.c
void	usage_export_replace_var(t_sdata *sdata, char *arg);
void	shell_export(t_sdata *sdata);
void	export_display(t_sdata *sdata);
//	pwd.c
void	pwd(t_sdata *sdata);
//	echo.c
void	echo(t_sdata *sdata);
//	cd.c
void	shell_cd(t_sdata *sdata);
//	exit.c
void	shell_exit(t_sdata *sdata);
int	usage_exit(char **argv);

//		Allocation
//	allocate_sdata.c
void	allocate_sdata(t_sdata *sdata, char **env);
t_cmd_lst	*allocate_cmd_elem(void);
t_env_lst	*allocate_env_lst_elem(char **line);

//		Deallocation
//	deallocate_sdata.c
void	deallocate_env_lst_elem(t_env_lst *elem);
void	free_arr(char **arr);
void	deallocate_sdata(t_sdata *sdata);
void	deallocate_cmd_elem(t_cmd_lst *cmd);

//		Utils
//	general_utils.c
void	*ft_bzero(size_t n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int		find_quotes(char *cmd, int i, char c);
int	nbr_of_word(char *av, char sep);
char	**str_to_word_arr(char *av, char sep);
//	str_arr_utils.c
char	**remove_str_from_arr(char **arr, char *str);
char	**cncat_arr(char **arr, char *str);
char	**dup_arr(char **arr);
//	str_manip
char	*ft_strncpy(char *dest, char *src, int n);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
char	*cncat(char *str1, char *str2, int ifree1, int ifree2);
char	*ft_strdup_free(char *src, int ifree);
char	*ft_substr_free(char *s, unsigned int start, size_t lenght, int ifree);
//	str_utils
int	tablen(char **tab);
int		nb_of_cmds(char *cmd);
int	ft_isdigit(int c);
int	is_number(char const *str, int i);
int	is_in_set(char c, char const *set);
size_t	len(const char *str);
//	ft_atoi.c
int	ft_atoi(const char *str);
//	list_utils.c
int	lenequal(char *str);
t_env_lst	*remove_elem(t_env_lst *list, char *arg);
t_env_lst	*add_elem(t_env_lst *list, char *arg);
char	**list_to_arr(t_env_lst *list);

#endif
