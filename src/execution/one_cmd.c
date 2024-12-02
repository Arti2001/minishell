/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command->c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student->42->fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:53:53 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/05 15:37:52 by amysiv           ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

int	is_herdoc(t_redirect *redirect)
{
	int	i;

	i = 0;
	if (redirect == NULL)
		return (0);
	while (redirect[i].filename != NULL)
	{
		if (redirect[i].type == HEREDOC_RE)
			return (1);
		else
			i++;
	}
	return (0);
}

void	execute_cmd(t_pars *pars, t_i_env *i_env)
{
	char	**env_array;

	env_array = back_to_array(i_env->env);
	path_handler(pars->cmd[0], i_env, &pars);
	if (pars->redir)
		redirect_check(pars);
	if (pars->path)
	{
		execve(pars->path, pars->cmd, env_array);
		ft_putstr_fd(pars->cmd[0], 2);
		shell_putendl_fd(": command not found", 2);
		exit(127);
	}
	free(pars->path);
	exit(i_env->err_code);
	//double_array_free(pars->cmd);
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
	init_siagtion(NON_INTERACTIVE);
	if (pid == 0 && pars->cmd != NULL)
	{
		execute_cmd(pars, i_env);
	}
	if (pars->cmd != NULL)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("error waitpid");
			exit(EXIT_FAILURE);
		}
	}
	init_siagtion(INTERACTIVE);
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
