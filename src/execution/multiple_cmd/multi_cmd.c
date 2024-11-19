/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:00:13 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/19 16:58:39 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void go_all_herdoc(t_pars *pars)
{
	t_pars	*tmp;
	
	tmp = pars;
	while (tmp != NULL)
	{
		
		if (is_herdoc(tmp->redir))
			run_herdoc(tmp->redir);
		tmp = tmp->next_process;
	}
}
int	run_multi_cmd(t_pars *pars, t_env *env)
{
	pid_t		pid;
	pid_t		pids[MAX_PROCESSES];
	int			fd[2];
	int			pid_count;
	int			count;

	pid_count = 0;
	count = 0;
	go_all_herdoc(pars);
	while (pars != NULL)
	{
		if (pars->next_process != NULL)
			 create_pipe(fd);
			//run_herdoc(pars->redir);
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
	return (wait_for_childs(pid_count, pids), 1);
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
