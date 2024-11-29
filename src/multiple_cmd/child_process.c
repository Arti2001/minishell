/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:00:02 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/29 15:39:46 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;


char	*join_nline(char *str)
{
	char *nline_str;

	nline_str = ft_strjoin(str, "\n");
	if (nline_str == NULL)
	{
		return	(NULL);
	}
	return (nline_str);
}
void	exit_code(int status, t_i_env *i_env, t_pars *pars)
{
	if (WIFEXITED(status))
	{
		i_env->err_code = WEXITSTATUS(status);
		if (i_env->err_code == 127)
		{
			ft_putstr_fd(pars->cmd[0], 2);
			shell_putendl_fd(": command not found", 2);
		}
	}
	else if (WTERMSIG(status))
		i_env->err_code = g_signal + 128;
	else
		i_env->err_code = -1;
}

int	wait_for_childs(int num_pid, pid_t *pids, t_i_env *i_env, t_pars *pars)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (i < num_pid)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid failed");
			exit(1);
		}
		exit_code(status, i_env, pars);
		i++;
		if (pars)
			pars = pars->next_process;
	}
	return (status);
}

/*try to store the read end  before  you fork*/
void	set_child(t_pars *pars, int fd_write, int p_num, t_env *env)
{
	if (pars->cmd == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	else if (check_redirection_type(p_num, pars, fd_write) == 0)
	{
		close(fd_write);
		perror ("pipe redirection failed");
		exit(EXIT_FAILURE);
	}
	else if (pars->redir != NULL)
	{
		redirect_check(pars);
	}
	if (is_builtin(pars->cmd[0]) == NO_BUILTIN)
	{
		path_hendler(env, &pars, pars->cmd[0]);
	}
}


void	my_dear_child(int fd, int process_num, t_pars *pars, t_i_env *i_env)
{
	char	**env_array;
	int		ret;

	set_child(pars, fd, process_num, i_env->env);
	if (is_builtin(pars->cmd[0]) != NO_BUILTIN)
	{
		ret = run_built_in(i_env, pars->cmd);
		exit(ret);
	}
	else
	{
		env_array = back_to_array(i_env->env);
		if (!env_array)
		{
			perror("Environment array creation failed");
			exit(EXIT_FAILURE);
		}
		if (pars->path)
			execve(pars->path, pars->cmd, env_array);
		else
		{
			double_array_free(pars->cmd);
			free(pars->path);
			exit(127);
		}
	}
}
