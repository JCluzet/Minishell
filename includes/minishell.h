/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:27:14 by ambelkac          #+#    #+#             */
/*   Updated: 2021/11/11 18:29:49 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

# define FIRST_ENV_CHAR_LIST "abcdefghijklmnopqrst\
uvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_/"
# define ENV_CHAR_LIST "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_=/+"
# define BUFFER_SIZE 4096
# define SHOW_PARSE 1

typedef struct s_len_file
{
	int		i;
	int		size;
}				t_len_file;

typedef struct s_path
{
	int		i;
	int		count;
	char	*tmpvar;
	char	*tmp;
}				t_path;

typedef struct s_doll
{
	int		i;
	int		j;
	int		count;
	char	*newcmd;
	char	*tmp;
	char	*tmpvar;
}				t_doll;

typedef struct s_quote
{
	int			simple_q;
	int			simple_q_indouble;
	int			double_q;
	int			double_q_insimple;
}				t_quote;

typedef struct s_skquo
{
	int			i;
	int			size;
}				t_skquo;

typedef struct s_redir
{
	int			nb_redir_in;
	int			nb_redir_out;
	int			nb_redir_app;
	int			nb_redir_hdoc;
}				t_redir;

typedef struct s_command_list
{
	struct s_command_list	*next;
	t_redir					*rdr;
	t_redir					*first_rdr;
	t_redir					*last_rdr;
	char					*cmd;
	char					**argv;
	char					*cmd_path;
	int						builtin_idx;
	char					**redir_ins;
	char					**redir_outs;
	char					**reddir_append;
	char					**reddir_heredoc;
	int						type_last_rdr_out;
	int						type_last_rdr_in;
	int						rdr_nb;
	int						*fd_stack;
	int						fd_nbr;
	int						last_fd_in;
	int						save_stdin;
}				t_cmd_lst;

typedef struct s_environement_list
{
	struct s_environement_list	*next;
	char						*name;
	char						*var;
}				t_env_lst;

typedef struct s_split_var
{
	int	i;
	int	j;
	int	save;
}				t_split_var;

typedef struct s_shell_data
{
	t_cmd_lst		*f_cmds;
	t_cmd_lst		*cmds;
	char			**env;
	t_env_lst		*env_lst;
	char			**bin_paths;
	unsigned char	lrval;
	int				cmd_idx;
	int				nb_of_cmds;
	int				cmd_nbr;
	int				save_stdin;
	int				save_stdout;
}				t_sdata;

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/environement/env_parsing.c                   */
/* -------------------------------------------------------------------------- */
int			env_var_additional_parsing(char *arg, int is_unset);
int			is_env_var_valid(char *arg, int is_unset);
int			does_env_var_exist(t_env_lst *env, char *var);
int			get_idx_var_in_env(char **env, char *var);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/environement/env_utils.c                    */
/* -------------------------------------------------------------------------- */
char		*get_env_var_from_name(t_env_lst *list, char *name);
char		*get_var_in_env(char **env, char *var);
char		*get_env_var_name_from_arg(char *arg);
t_skquo		skip_qu_file(t_skquo skqu, char *cmd, char *file);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/memory/allocate_sdata.c                     */
/* -------------------------------------------------------------------------- */
t_cmd_lst	*allocate_cmd_elem(void);
t_env_lst	*allocate_env_lst_elem(char **line);
int			allocate_env_lst(t_sdata *sdata, char **env);
void		allocate_sdata(t_sdata *sdata, char **env);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/memory/free_arr.c                        */
/* -------------------------------------------------------------------------- */
void		free_arr(char **arr);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/memory/dealocate_sdata.c                    */
/* -------------------------------------------------------------------------- */
void		deallocate_cmd_elem(t_cmd_lst *elem);
void		deallocate_cmd_list(t_cmd_lst *cmds);
void		deallocate_env_lst_elem(t_env_lst *elem);
int			deallocate_env_lst(t_env_lst *list);
void		deallocate_sdata(t_sdata *sdata);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/str_utils.c                        */
/* -------------------------------------------------------------------------- */
int			tablen(char **tab);
int			ft_isdigit(int c);
int			is_number(char const *str, int i);
int			is_in_set(char c, char const *set);
int			len(const char *str);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/str_manip.c                        */
/* -------------------------------------------------------------------------- */
char		*ft_strncpy(char *dest, char *src, int n);
char		*ft_strncat(char *dest, char *src, unsigned int nb);
char		*cncat(char *str1, char *str2, int ifree1, int ifree2);
char		*ft_strdup_free(char *src, int ifree);
char		*ft_substr_free(char *s, unsigned int start,
				size_t lenght, int ifree);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/str_quote.c                        */
/* -------------------------------------------------------------------------- */
int			duoquote(char *cmd, int v);
int			is_insquote(char *cmd, int v);
int			skip_quotes_arg(char *cmd, int i);
char		**skip_quotes_split(const char *s, int i, char **split, int j);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/list_utils.c                       */
/* -------------------------------------------------------------------------- */
int			lenequal(char *str);

/* -------------------------------------------------------------------------- */
/*                  FILE = srcs/utils/even_more_str_utils.c                   */
/* -------------------------------------------------------------------------- */
int			len_x(char const *str, char c);
char		*get_file_redir(char *cmd, char *file);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		putstr_err(char *str);
int			is_maj(char c);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/utils/dollars_utils.c                      */
/* -------------------------------------------------------------------------- */
int			skip_var(char *str);
int			int_len(int i);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/utils/get_next_line.c                      */
/* -------------------------------------------------------------------------- */
size_t		lennewline(char *str);
int			read_fd(int fd, char **str);
int			is_there_save(char **str, char **save);
int			cut_line(char **save, char **str);
int			get_next_line(int fd, char **line);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/utils/more_str_utils.c                     */
/* -------------------------------------------------------------------------- */
int			empty_str(char *str);
int			skip_blank(char *cmd);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/utils/env_lst_utils.c                      */
/* -------------------------------------------------------------------------- */
t_env_lst	*remove_first_elem(t_env_lst *list);
void		remove_last_elem(t_env_lst *list, t_env_lst *tmp);
t_env_lst	*remove_elem(t_env_lst *list, char *arg);
t_env_lst	*add_elem(t_env_lst *list, char *arg);
int			does_elem_exists(t_env_lst *list, char *arg);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/utils/general_utils.c                      */
/* -------------------------------------------------------------------------- */
void		*ft_bzero(size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			nbr_of_word(char *av, char sep);
int			find_quotes(char *cmd, int i, char c);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/utils/str_arr_utils.c                      */
/* -------------------------------------------------------------------------- */
char		**new_arr(char *str);
char		**extend_arr(char **arr, char *str);
char		**cncat_arr(char **arr, char *str);
char		**remove_str_from_arr(char **arr, char *str);
char		**dup_arr(char **arr);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/utils/str_to_word_arr.c                     */
/* -------------------------------------------------------------------------- */
void		skip_sep_char(char *av, char sep, int *i);
char		*put_word_in_arr(char *av, int i, int save);
char		**str_to_word_arr(char *av, char sep);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/split_env.c                        */
/* -------------------------------------------------------------------------- */
char		**set_word_in_tab(char **arr, char *line, int i);
char		**split_env(char *line, char sep);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/utils/ft_atoi.c                         */
/* -------------------------------------------------------------------------- */
int			ft_atoi(const char *str);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/builtins/exit.c                         */
/* -------------------------------------------------------------------------- */
void		shell_exit(t_sdata *sdata);
int			usage_exit(char **argv);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/builtins/unset.c                        */
/* -------------------------------------------------------------------------- */
void		shell_unset(t_sdata *sdata);
int			usage_unset(char ***env, char *var);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/builtins/env.c                         */
/* -------------------------------------------------------------------------- */
void		display_env(t_sdata *sdata);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/builtins/pwd.c                         */
/* -------------------------------------------------------------------------- */
void		pwd(t_sdata *sdata);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/builtins/export.c                        */
/* -------------------------------------------------------------------------- */
void		export_display(t_sdata *sdata);
void		usage_export_replace_var(t_sdata *sdata, char *arg);
void		export_replace_var(t_sdata *sdata);
void		shell_export(t_sdata *sdata);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/builtins/cd.c                          */
/* -------------------------------------------------------------------------- */
void		update_env_cd(t_sdata *sdata, char *old_pwd);
char		*get_abs_path(char *path, int free_path);
void		change_directory_home(t_sdata *sdata);
void		shell_cd(t_sdata *sdata);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/builtins/echo.c                         */
/* -------------------------------------------------------------------------- */
void		putstr_skipquotes(char *str);
void		putstr_quoteless(char *str);
void		display_every_arg(char **argv, int start);
int			is_dash_n_option(char *option);
void		echo(t_sdata *sdata);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/execution/dispatcher.c                     */
/* -------------------------------------------------------------------------- */
int			manage_pipe_dups(t_cmd_lst *cmds, pid_t pid, int *fd);
void		invalid_cmd(t_sdata *sdata, t_cmd_lst *cmds);
int			execute_builtins(t_sdata *sdata, int *fd, int save_stdout);
int			execute_binary(t_sdata *sdata, int *fd);
void		invalid_cmd_path_error(t_sdata *sdata);
void		execution_dispatcher(t_sdata *sdata);

/* -------------------------------------------------------------------------- */
/*               FILE = srcs/execution/execution_redirection.c                */
/* -------------------------------------------------------------------------- */
int			heredoc_error(char *limit);
int			manage_heredoc(char *limit, int l_fd_in, int save_stdin);
int			open_outfile(char *path, int in);
int			open_infile(t_cmd_lst *cmds, char *path, int out);
int			manage_redir_fd(t_cmd_lst *cmd, char **paths, int in, int out);
int			priority_redir_in(t_cmd_lst *cmds);
int			priority_redir_out(t_cmd_lst *cmds);
int			dispatch_redir_types(t_cmd_lst *cmds);

/* -------------------------------------------------------------------------- */
/*                  FILE = srcs/execution/fd_stack_manage.c                   */
/* -------------------------------------------------------------------------- */
int			*extend_fd_stack(int *fd_stack, int fd_len, int fd);
void		add_fd_to_stack(t_cmd_lst *cmds, int fd);
void		clear_fd_stack(t_cmd_lst *cmds);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/errors/return_functions.c                    */
/* -------------------------------------------------------------------------- */
int			error_print_free(int rval, char *str, t_sdata *sdata);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/parsing/stockredir.c                      */
/* -------------------------------------------------------------------------- */
int			malloc_and_stock_redir(t_cmd_lst *c, char *cmd);
char		**malloc_redir_next(t_cmd_lst *cmds, char *cmd, int size, int type);
t_redir		initrdr(void);
t_redir		*initrdr2(void);
int			strlen_cmd_without_rdr(char *cmd);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/parsing/replace_dollars.c                    */
/* -------------------------------------------------------------------------- */
char		*str_find_var(char *str);
int			strlen_pathcmd(t_sdata *t_sdata, char *str);
char		*put_int_str(int nb_len, char *cmd, int count, int lrval);
char		*replace_dollars(char *old_cmd, t_sdata *sdata);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/parsing/linklist.c                       */
/* -------------------------------------------------------------------------- */
t_cmd_lst	*init_linkedlist(void);
t_cmd_lst	*insertion_linklist(t_cmd_lst *cmds);
void		printf_linked_list(t_cmd_lst *cmd);
void		print_cmds(t_cmd_lst *cmds, int v, int i);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/parsing/parse_line.c                      */
/* -------------------------------------------------------------------------- */
t_cmd_lst	*parse_line(t_sdata *sdata, char *line);
int			check_forbidden(char *str);
int			pipe_check(char *str);
int			quotes_check(char *str);
int			checkquotes(char c, t_quote *qt);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/parsing/redir.c                         */
/* -------------------------------------------------------------------------- */
char		*fill_file_rdr(char *cmd, int nb, int type, char *file);
int			find_size_rdr(char *cmd, int nb, int type);
int			find_lenghtwq(char *cmd);
int			find_lenght_file(char *cmd);
void		get_size_redir(t_cmd_lst *cmds, char *cmd);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/parsing/check_cmd_executable.c                 */
/* -------------------------------------------------------------------------- */
char		**get_paths_from_env(t_env_lst *env);
char		*is_cmd_in_path(char *cmd, char **paths);
char		*does_binary_file_exists(char *cmd);
char		*is_cmd_executable(char *cmd, t_sdata *sdata);
int			is_builtin(char *cmd);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/parsing/fill_cmds.c                       */
/* -------------------------------------------------------------------------- */
void		fill_cmds(t_sdata *data, t_cmd_lst *cmds, char *cmd);
char		*rmv_rdr_from_cmd(char *cmd);
char		*find_andsupp_rdr(char *cmd, char *newcmd, int count);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/parsing/ft_split_space.c                    */
/* -------------------------------------------------------------------------- */
char		**split_the_pipe(char const *s);
int			nb_of_args(char *cmd);
char		**split_arg(char *s);
char		*word_dup(const char *str, int start, int finish);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/main/shell_loop.c                        */
/* -------------------------------------------------------------------------- */
int			shell_loop(t_sdata *sdata);
int			check_line(char *line);
int			redir_check(char *cmd);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/main/minishell.c                        */
/* -------------------------------------------------------------------------- */
int			main(int ac, char **argv, char **env);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/signal/manage_signal.c                     */
/* -------------------------------------------------------------------------- */
void		handler(int signum);
void		assign_signals_handler(void);

int			dispatch_redir_types(t_cmd_lst *cmds);
int			open_infile(t_cmd_lst *cmds, char *path, int out);
int			open_outfile(char *path, int in);
int			manage_heredoc(char *limit, int l_fd_in, int save_stdin);
int			priority_redir_out(t_cmd_lst *cmds);
int			priority_redir_in(t_cmd_lst *cmds);
char		**remove_str_from_arr(char **arr, char *str);
void		child_handler(int signum);
int			execute_builtins(t_sdata *sdata, int *fd, int save_stdout);
#endif
