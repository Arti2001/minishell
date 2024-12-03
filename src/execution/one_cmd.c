/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:07:38 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 21:09:08 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	execute_cmd(t_pars *pars, t_i_env *i_env)
{
	char	**env_array;

	env_array = back_to_array(i_env->env);
	if (pars->cmd)
		path_handler(pars->cmd[0], i_env, &pars);
	if (pars->redir)
		redirect_check(pars);
	if (pars->path)
	{
		execve(pars->path, pars->cmd, env_array);
		ft_putstr_fd(pars->cmd[0], 2);
		shell_putendl_fd(": command not found", 2);
		free(pars->path);
		exit(127);
	}
	double_array_free(pars->cmd);
	exit(i_env->err_code);
}

int	new_proccess(t_pars *pars, t_i_env *i_env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("pid filed");
		exit(EXIT_FAILURE);
	}
	init_sigaction(NON_INTERACTIVE);
	if (pid == 0 && (pars->cmd != NULL || pars->redir))
	{
		execute_cmd(pars, i_env);
	}
	if (pars->cmd != NULL || pars->redir)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("error waitpid");
			exit(EXIT_FAILURE);
		}
	}
	init_sigaction(INTERACTIVE);
	return (status);
}

int	run_single_cmd(t_pars *pars, t_i_env *i_env)
{
	int		exit_status;
	int		ret;

	ret = 0;
	exit_status = new_proccess(pars, i_env);
	if (WIFEXITED(exit_status))
	{
		ret = WEXITSTATUS(exit_status);
		return (ret);
	}
	else if (WTERMSIG(exit_status))
	{
		ret = g_signal + 128;
		return (ret);
	}
	else
		return (-1);
}
