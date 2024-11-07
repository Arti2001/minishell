// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   multi_cmd.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/01 14:09:40 by amysiv            #+#    #+#             */
// /*   Updated: 2024/11/05 20:31:03 by amysiv           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// int redir_first_proc(t_pars *pars,  int fd[2])
// {
// 	if (dup2(fd[1], STDOUT_FILENO) == -1)
// 	{
// 		perror("Failed to redirect the write end");
// 		return (0);
// 	}
// 	if (close(fd[1]) == -1)
// 	{
// 		perror("Failed to close the write end");
// 		return (0);
// 	}
// 	return (1);
// }
// int redir_middele_proc(t_pars *pars,  int fd[2])
// {
// 	if (dup2(pars->fd_in, STDIN_FILENO) == -1)
// 	{
// 		perror("Failed to redirect the read end");
// 		return (0);
// 	}
// 	if (close(pars->fd_in) == -1)
// 	{
// 		perror("Failed to close the read end");
// 		return (0);
// 	}
// 	if (dup2(fd[1], STDOUT_FILENO) == -1)
// 	{
// 		perror("Failed to redirect the write end");
// 		return (0);
// 	}
// 	if (close(fd[1]) == -1)
// 	{
// 		perror("Failed to close the write end");
// 		return (0);
// 	}

// }
// int redir_last_proc(t_pars *pars,  int fd[2])
// {
// 	if (dup2(pars->fd_in, STDIN_FILENO) == -1)
// 	{
// 		perror("Failed to redirect the read end");
// 		return (0);
// 	}
// 	if (close(fd[0]) == -1)
// 	{
// 		perror("Failed to close the read end");
// 		return (0);
// 	}

// }
// void	check_redirection_type(int	process_num, t_pars *pars, int fd[2])
// {
// 	if (process_num == 0 && pars->next_process != NULL)
// 		redir_first_proc(pars, fd[2]);
// 	else if (process_num != 0 && pars->next_process != NULL)
// 		redir_middle_proc(pars, fd[2]);
// 	else if (process_num != 0 && pars->next_process == NULL)
// 		redir_last_proc(pars, fd[2]);
// }
// /*try to store the read end  before  you fork*/
// void	my_dear_child(int fd_pipe[2], int	process_num, t_pars *pars, t_env *env)
// {
// 	char	**env;

// 	env = back_to_array(env);
// 	check_redirection_type(process_num, pars, fd_pipe[2]);

// 	execve(pars->path, pars->cmd, env);
// 	ft_putstr_fd(pars->cmd[0], 2);
// 	ft_putendl_fd(": command not found", 2);
// 	double_array_free(pars->cmd);
// 	free(pars->	path);
// }
// //int	run_multi_cmd(t_pars *pars, t_env *env)
// // {
// //	pid_t		pid;
// //	int			fd[2];


// //	set_extern_cmd_path(pars, env);
// //	while (pars != NULL)
// //	{
// //		if (pipe(fd) == -1)
// //		{
// //			perror("Failed to create a pipe in multi cmd");
// //			return (1);
// //		}
// //		pid = fork();
// //		if (pid == -1)
// //		{
// //			perror("Failed to fork in multi cmd");
// //			return (1);
// //		}
// //		if (pid == 0)
// //		{
// //			my_dear_child(fd, pars, env);
// //		}
// //		pars = pars->next_process;
// //	}
// //	return (1);
// //}


// int	run_multi_cmd(t_pars *pars, t_env *env)
//  {
// 	pid_t		pid;
// 	int			fd[2];
// 	int			process_num;

// 	process_num = 0;
// 	set_extern_cmd_path(pars, env);
// 	while (pars != NULL)
// 	{
// 		pipe(fd);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			close(fd[0]);
// 			my_dear_child(fd, process_num, pars, env);
// 		}
// 		waitpid(pid, NULL, 0);
// 		pars->next_process->fd_in = fd[0];
// 		close(fd[0]);
// 		close(fd[1]);
// 		pars = pars->next_process;
// 		process_num++;
// 	}
// 	return (1);
// }