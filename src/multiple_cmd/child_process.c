/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:00:02 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/28 13:45:01 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_childs(int num_pid, pid_t *pids)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (i < num_pid)
	{
		if (waitpid(pids[i], &status, 0)  == -1)
		{
			perror("waitpid failed");
			exit(1);
		}
		i++;
	}
	return (status);
}

/*try to store the read end  before  you fork*/
void	set_child(t_pars *pars, t_env *env, int fd_write, int p_num)
{
	if (pars->cmd == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	if (check_redirection_type(p_num, pars, fd_write) == 0)
	{
		close(fd_write);
		perror ("pipe redirection failed");
		exit(EXIT_FAILURE);
	}
	if (pars->redir != NULL)
	{
		redirect_check(pars);
	}
	if (access(pars->cmd[0], X_OK | F_OK) == 0)
	{
		pars->path = pars->cmd[0];
	}
	else
	{
		path_hendler(env, &pars, pars->cmd[0]);
	}
}

void	my_dear_child(int fd, int process_num, t_pars *pars, t_i_env *i_env)
{
	char	**env_array;

	env_array = back_to_array(i_env->env);
	if (!env_array)
	{
		close(fd);
		perror("Environment array creation failed");
		exit(EXIT_FAILURE);
	}
	set_child(pars, i_env->env, fd, process_num);
	if (is_builtin(pars->cmd[0]) != NO_BUILTIN)
	{
		run_built_in(i_env, pars->cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(pars->path, pars->cmd, env_array);
		double_array_free(pars->cmd);
		free(pars->path);
		exit(127);
	}
}
