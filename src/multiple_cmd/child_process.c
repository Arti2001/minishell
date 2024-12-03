/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:00:02 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 17:54:44 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

char	*join_nline(char *str)
{
	char	*nline_str;

	nline_str = ft_strjoin(str, "\n");
	if (nline_str == NULL)
	{
		return (NULL);
	}
	return (nline_str);
}

int	exit_code(int status, t_pars *pars)
{
	int	ret;

	ret = 0;
	if (WIFEXITED(status))
	{
		ret = WEXITSTATUS(status);
		if (ret == 127)
		{
			ft_putstr_fd(pars->cmd[0], 2);
			shell_putendl_fd(": command not found", 2);
		}
	}
	else if (WTERMSIG(status))
		ret = g_signal + 128;
	else
		ret = -1;
	return (ret);
}

int	wait_for_childs(int num_pid, pid_t *pids, t_pars *pars)
{
	int		i;
	int		ret;
	int		status;
	

	i = 0;
	ret = 0;
	status = 0;
	while (i < num_pid)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid failed");
			exit(EXIT_FAILURE);
		}
		ret = exit_code(status, pars);
		i++;
		if (pars)
			pars = pars->next_process;
	}
	return (ret);
}

/*try to store the read end  before  you fork*/
void	set_child(t_pars *pars, int fd_write, int p_num, t_i_env *i_env)
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
		path_handler(pars->cmd[0], i_env, &pars);
	}
}

void	my_dear_child(int fd, int process_num, t_pars *pars, t_i_env *i_env)
{
	char	**env_array;
	int		ret;

	ret = 0;
	set_child(pars, fd, process_num, i_env);
	if (is_builtin(pars->cmd[0]) != NO_BUILTIN)
	{
		ret = run_built_in(i_env, pars);
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
		{
			execve(pars->path, pars->cmd, env_array);
			free(pars->path);
			exit(127);
		}
		double_array_free(pars->cmd);
		exit(i_env->err_code);
	}
}
