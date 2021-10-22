/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:30:59 by ambelkac          #+#    #+#             */
/*   Updated: 2021/10/22 14:38:07 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// i#nclude "../../includes/minishell.h"


// void	execute_cmd(int ac, char **av, t_piped pdata, int i)
// {
// 	char	**cmd_arg;
// 	char	*cmd_path;

// 	cmd_arg = ft_split(av[i], ' ');
// 	if (i == 2 && pdata.fdi == -1)
// 		print_return(-1, "Invalid infile");
// 	if (i == ac - 2 && pdata.fdo == -1)
// 		print_return(-1, "Invalid outfile");
// 	cmd_path = find_cmd_path(pdata, cmd_arg[0]);
// 	if (execve(cmd_path, cmd_arg, pdata.env) == -1)
// 		print_return(1, cncat("pipex: command not found: ", cmd_arg[0], 0, 0));
// }

// void	manage_heredoc(char **av, t_piped pdata)
// {
// 	char	*line;

// 	line = NULL;
// 	write(1, ">", 1);
// 	get_next_line(0, &line);
// 	while (ft_strncmp(av[2], line, len(av[2])))
// 	{
// 		write(pdata.fdi, line, len(line));
// 		free(line);
// 		line = NULL;
// 		write(pdata.fdi, "\n", 1);
// 		write(1, ">", 1);
// 		get_next_line(0, &line);
// 	}
// 	close(pdata.fdi);
// 	pdata.fdi = open("/tmp/.tmp_heredoc", O_RDONLY);
// }

// void	manage_process_duplication(char **av, int ac, t_piped pdata, int i)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (!pid)
// 	{
// 		close(pdata.fd[0]);
// 		dup2(pdata.fd[1], 1);
// 		execute_cmd(ac, av, pdata, i);
// 	}
// 	else
// 	{
// 		close(pdata.fd[1]);
// 		dup2(pdata.fd[0], 0);
// 	}
// }

// int	fork_process(int ac, char **av, t_piped pdata)
// {
// 	int		i;

// 	dup2(pdata.fdi, 0);
// 	while (i < ac - 1)
// 	{
// 		if (i < ac - 2)
// 			pipe(pdata.fd);
// 		else
// 			dup2(pdata.fdo, 1);
// 		manage_process_duplication(av, ac, pdata, i);
// 		waitpid(-1, NULL, 0);
// 		++i;
// 	}
// 	print_free(0, NULL, 1, pdata);
// 	return (0);
// }
