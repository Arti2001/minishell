/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:09:40 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/10 15:25:30 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void wait_for_childs(int num_pid, pid_t *pids)
{
	int		i;

	i = 0;
	while (i < num_pid)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}


int redir_first_proc(int fd_write_end)
{
	if (dup2(fd_write_end, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect the write end");
		return (0);
	}

	if (close(fd_write_end) == -1)
	{
		perror("Failed to close the write end");
		return (0);
	}
	return (1);
}

int redir_mid_proc(t_pars *pars, int fd_write_end)
{
	if (dup2(pars->fd_in, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect the read end");
		return (0);
	}
	if (close(pars->fd_in) == -1)
	{
		perror("Failed to close the read end");
		return (0);
	}
	if (dup2(fd_write_end, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect the write end");
		return (0);
	}
	if (close(fd_write_end) == -1)
	{
		perror("Failed to close the write end");
		return (0);
	}
	return (1);
}

int redir_last_proc(t_pars	*pars)
{
	if (dup2(pars->fd_in, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect the read end");
		return (0);
	}
	if (close(pars->fd_in) == -1)
	{
		perror("Failed to close the read end");
		return (0);
	}
	return (1);
}
int	check_redirection_type(int	process_num, t_pars *pars, int fd_write_end)
{
	if (process_num == 0 && pars->next_process != NULL)
	{
		return(redir_first_proc(fd_write_end));
	}
	else if (process_num != 0 && pars->next_process != NULL)
	{
		return(redir_mid_proc(pars, fd_write_end));
	}
	else if (process_num != 0 && pars->next_process == NULL)
	{
		return(redir_last_proc(pars));
	}
	return (0);
}
/*try to store the read end  before  you fork*/
void	my_dear_child(int fd_write_end, int	process_num, t_pars *pars, t_env *env)
{
	char	**environment;

	/*translate environment to double array*/
	path_hendler(env, &pars, pars->cmd[0]);
	environment = back_to_array(env);
	if (!environment)
	{
		close(fd_write_end);
		perror("Environment array creation failed");
		exit(errno);
	}
	if (check_redirection_type(process_num, pars, fd_write_end) == 0)
	{
		close(fd_write_end);
		perror ("pipe redirection failed");
		exit(EXIT_FAILURE);
	}
	//redirect_check(pars);
	if (is_builtin(pars->cmd[0]) != NO_BUILTIN)
	{
		run_built_in(&env, pars->cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(pars->path, pars->cmd, environment);
		ft_putstr_fd(pars->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		double_array_free(pars->cmd);
		free(pars->	path);
		exit(127);
	}
}


void		create_pipe(int	fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("Failed to create a pipe ");
		exit (errno);
	}
}

pid_t		create_fork()
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Failed to fork");
		exit(errno);
	}
	return (pid);
}

void	handle_child_process(int fd[2], int	p_num, t_pars *pars, t_env *env)
{
	if (pars->next_process != NULL)
	{
		if (close(fd[0]) == -1)
		{
			perror("Failed to close read end");
			exit(errno);
		}
	}
	my_dear_child(fd[1], p_num, pars, env);
}
void	handle_parent_process(int fd[2], t_pars *pars, int	p_num)
{
	if (pars->next_process != NULL)
	{
		if (close(fd[1]) == -1)
		{
			perror("Failed to close write end");
			exit(errno);
		}
		pars->next_process->fd_in = fd[0];
	}
	if (p_num != 0)
	{
		if (close(pars->fd_in) == -1)
		{
			perror("Failed to close read end");
			exit(errno);
		}
	}
}

// int	run_multi_cmd(t_pars *pars, t_env *env)
//  {
// 	pid_t		pid;
// 	pid_t		pids[MAX_PROCESSES];
// 	int			fd[2];
// 	int			process_num;
// 	int			pid_count;
	
// 	process_num = 0;
// 	pid_count = 0;
// 	while (pars != NULL)
// 	{
// 		if (pars->next_process != NULL)
// 			if (pipe(fd) == -1)
// 			{
// 				perror("Failed to create a pipe ");
// 				return (errno);
// 			}
// 		pid = fork();
// 		pids[pid_count++] = pid;
// 		if (pid == -1)
// 		{
// 			perror("Failed to fork");
// 			return (errno);
// 		}
// 		if (pid == 0)
// 		{
// 			if (pars->next_process != NULL)
// 				close(fd[0]);
// 			my_dear_child(fd[1], process_num, pars, env);
// 		}
// 		else
// 		{
// 			if (pars->next_process != NULL)
// 			{
// 				close(fd[1]);
// 				pars->next_process->fd_in = fd[0];
// 			}
// 			if (process_num != 0)
// 				close(pars->fd_in);

// 			pars = pars->next_process;
// 			process_num++;
// 		}
// 	}
// 	wait_for_childs(pid_count, pids);
// 	return (1);
// }

int	run_multi_cmd(t_pars *pars, t_env *env)
{
	pid_t		pid;
	pid_t		pids[MAX_PROCESSES];
	int			fd[2];
	int			pid_count;
	int			count;

	pid_count = 0;
	count = 0;
	while (pars != NULL)
	{
		if (pars->next_process != NULL)
			 create_pipe(fd);
		pid = fork();
		pids[pid_count++] = pid;
		if (pid == 0)
			handle_child_process(fd, count, pars, env);
		else
		{
			handle_parent_process(fd, pars, count);
			pars = pars->next_process;
			count++;
		}
	}
	wait_for_childs(pid_count, pids);
	return (1);
}






//int	ft_close (int *ptr)
//{
//	int	ret;
	
//	ret = 0;
//	if (*ptr != -1)
//	{
//		ret = close(*ptr);
//		*ptr = -1;
//	}
//	else
//		printf("fd was already closed\n");
//	return (ret);
//}
