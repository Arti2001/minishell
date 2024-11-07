/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:09:40 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/07 19:53:50 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void wait_for_childs(pid_t num_pid, pid_t *pids)
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
		return(redir_first_proc(fd_write_end));
	else if (process_num != 0 && pars->next_process != NULL)
		return(redir_mid_proc(pars, fd_write_end));
	else if (process_num != 0 && pars->next_process == NULL)
		return(redir_last_proc(pars));
	return (0);
}
/*try to store the read end  before  you fork*/
void	my_dear_child(int fd_write_end, int	process_num, t_pars *pars, t_env *env)
{
	char	**environment;
	
	/*translate environment to double array*/
	environment = back_to_array(env);
	path_hendler(env, &pars, pars->cmd[0]);
	if (!environment)
	{
		perror("Environment array creation failed");
		exit(errno);
	}
	if (check_redirection_type(process_num, pars, fd_write_end) == 0)
	{
		perror ("pipe redirection failed");
		exit(EXIT_FAILURE);
	}
	//redirect_check(pars);
	execve(pars->path, pars->cmd, environment);
	ft_putstr_fd(pars->cmd[0], 2);
	ft_putendl_fd(": command not found", 2);
	double_array_free(pars->cmd);
	free(pars->	path);
	exit(127);
}

int	run_multi_cmd(t_pars *pars, t_env *env)
 {
	pid_t		pid;
	pid_t		pids[MAX_PROCESSES];
	int			fd[2];
	int			process_num;
	int			pid_count;
	
	/*sets path for each command*/

	process_num = 0;
	pid_count = 0;
	while (pars != NULL)
	{
		if (pars->next_process != NULL)
			if (pipe(fd) == -1)
			{
				perror("Failed to create a pipe ");
				return (errno);
			}
		pid = fork();
		if (pid == -1)
		{
			perror("Failed to fork");
			return (errno);
		}
		if (pid == 0)
		{
			if (pars->next_process != NULL)
				close(fd[0]);
			my_dear_child(fd[1], process_num, pars, env);
		}
		else
		{
			pids[pid_count++] = pid;
			if (pars->next_process != NULL)
			{
				close(fd[1]);
				pars->next_process->fd_in = fd[0];
			}
			pars = pars->next_process;
			process_num++;
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
