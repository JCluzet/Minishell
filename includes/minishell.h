/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:27:14 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/08 20:03:36 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
# include <signal.h>
#include <fcntl.h>
# include <sys/wait.h>

# define FIRST_ENV_CHAR_LIST "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_/"
# define ENV_CHAR_LIST "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_=/"
# define BUFFER_SIZE 4096

typedef struct  s_quote
{
		int simple_q;
		int simple_q_indouble;
		int double_q;
		int double_q_insimple;
}				t_quote;

typedef struct	s_redir
{
	int			nb_redir_in; // 1    >
	int			nb_redir_out; // 2   <
	int			nb_redir_app; // 3   >>
	int			nb_redir_hdoc; // 4  <<
}				t_redir;

typedef struct	s_command_list
{
	char		*cmd;//		trimmed cmd name                                     >> nom de la commande tapé
	char		**argv;//	Nullterminated arg of cmd                           >> arguments que prennent la commande ou NULL si sans argument
	char		*cmd_path;// Valid bath to executable file, set to NULL if none  >> path vers l'executable (si existant)
	int			builtin_idx; // if > 7 is a builtin, if == 7 is not              >> le numero du builtin ( 7 si non existant )
	t_redir		*rdr;
	char	**redir_ins; // REDIR_IN c'est les redirections a gauche '<' pour une cmd qui va contenir genre les nom des fichiers in 
	char	**redir_outs; // REDIR_OUT c'est les redirections a droite '>'
	char	**reddir_append; // APPEND c'est les double redir a droite '>>'
	char	**reddir_heredoc; // HEREDOC c'est les double redir a gauche '<<'

	t_redir		*last_rdr;
	int		type_last_rdr_out;
	int		type_last_rdr_in;
	int		rdr_nb;

	t_redir *first_rdr;

	int			*fd_stack;
	int			fd_nbr;
	int			last_fd_in;
	int			save_stdin;

	struct s_command_list	*next;
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
	int			cmd_idx;
	int			nb_of_cmds;
	int			cmd_nbr;
	int			save_stdin;
	int			save_stdout;
}				t_sdata;

t_sdata	*g_sdata;

// Testing

void	print_cmds(t_cmd_lst *cmds, char *cmd, int v, int i);

//		Main
//	shell_loop.c
int	shell_loop(t_sdata *sdata);

//		Parsing
//	parse_line
int		is_maj(char c);
int		pipe_check(char *str);
int		stock_redir(t_cmd_lst *cmds, char *cmd);
char		**split_thepipe(char const *s, char c);
int		stock_redir(t_cmd_lst *cmds, char *cmd);
static char	*word_dup(const char *str, int start, int finish);
int issep(char c);
int		check_line(char *line);
int is_double_redir(char c, char c1);
int		strlen_pathcmd(t_sdata *t_sdata, char *str);
int	isspace_behind(char *str, int i);


static char	*word_dup(const char *str, int start, int finish);
static int	count_words(const char *str, char c);

t_cmd_lst	*parse_line(t_sdata *sdata, char *line);
t_cmd_lst	*init_linkedlist(void);

t_cmd_lst	*insertion_linklist(t_cmd_lst *cmds);
void			printf_linked_list(t_cmd_lst *cmd, int nb);
int		check_error(t_cmd_lst *cmd);
int	is_builtin(char *cmd);
int		quotes_check(char *str);
int		checkquotes(char c, t_quote *qt);
char 	*replace_dollars(char *str, t_sdata *sdata);

//	check_cmd_executable.c
char	*is_cmd_executable(char *cmd, t_sdata *sdata);
//	fill_cmds.c
void	fill_cmds(t_sdata *data, t_cmd_lst *cmds, char *cmd);
char		**split_thespace(char const *s, char c);
static int	count_words_space(const char *str, char c);
t_cmd_lst	*split_cmds(char *cmd, t_cmd_lst *cmds);

//		Execution
//	dispatcher.c
void	execution_dispatcher(t_sdata *sdata, t_cmd_lst *cmds);

//		Environement
//	env_parsing.c
char	*get_env_var_from_name(t_env_lst *list, char *name);
int	does_env_var_exist(t_env_lst *env, char *var);
char	*get_env_var_name_from_arg(char *arg);
int	is_env_var_valid(char *arg, int is_unset);
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
void	deallocate_cmd_list(t_cmd_lst *cmd);

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
int		find_squotes(char *cmd, int i, char c);
char	*ft_strncpy(char *dest, char *src, int n);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
char	*cncat(char *str1, char *str2, int ifree1, int ifree2);
char	*ft_strdup_free(char *src, int ifree);
char	*ft_substr_free(char *s, unsigned int start, size_t lenght, int ifree);
//	get_next_line.c
int	get_next_line(int fd, char **line);
//	str_utils
int	tablen(char **tab);
int		is_insquote(char *cmd, int v);
int		is_indquote(char *cmd, int v);
int		nb_of_cmds(char *cmd);
int	ft_isdigit(int c);
int	is_number(char const *str, int i);
int	is_in_set(char c, char const *set);
char 	*str_x(char *str);
int		len_x(char const *str, char c);
int empty_str(char *str);
size_t	len(const char *str);
//	ft_atoi.c
int	ft_atoi(const char *str);
//	list_utils.c
int	lenequal(char *str);
t_env_lst	*remove_elem(t_env_lst *list, char *arg);
t_env_lst	*add_elem(t_env_lst *list, char *arg);
char	**list_to_arr(t_env_lst *list);
int		error_print_free(int rval, char *str, t_sdata *sdata);

//	Signal
void		assign_signals_handler(void);

// REDIR TESTING

t_redir	initrdr(void);
void get_size_redir(t_cmd_lst *cmds, char *cmd);
char		*fill_file_rdr(char *cmd, int nb, int type, char *file);
int		get_first_rdr_idx(char *cmd);
int		get_last_rdr_idx(char *cmd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*rmv_rdr_from_cmd(char *cmd);
int		is_cmd_after_file(char *cmd, int nb);
char	*ft_strdup(char *src);
int		cut_first_redir(char *line, t_cmd_lst *cmd);
char*	get_file_redir(char *cmd, char *file);
t_redir	*initrdr2(void);
char	*rmv_quotes_from_cmd(char *cmd);
int		skip_blank(char *cmd);
int		find_lenght_file(char *cmd);
int		find_size_rdr(char *cmd, int nb, int type);
char	**malloc_redir_next(t_cmd_lst *cmds,char *cmd, int size, int type);
int	malloc_and_stock_redir(t_cmd_lst *cmds, char *cmd);
int		stock_redir(t_cmd_lst *cmds, char *cmd);
int	end_first_rdr(char *cmd);
int		redir_check(char *cmd);
int		is_insquote(char *cmd, int v);

void		clear_fd_stack(t_cmd_lst *cmds);
void		add_fd_to_stack(t_cmd_lst *cmds, int fd);
int			dispatch_redir_types(t_cmd_lst *cmds);
#endif
