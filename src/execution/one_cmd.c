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

int		is_herdoc(t_redirect *redirect)
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

void	execute_cmd(t_pars *pars, t_env *env)
{
	char	**env_array;

	env_array = back_to_array(env);
	path_hendler(env, &pars, pars->cmd[0]);
	redirect_check(pars);
	execve(pars->path, pars->cmd, env_array);
	ft_putstr_fd(pars->cmd[0], 2);
	ft_putendl_fd(": command not found", 2);
	double_array_free(pars->cmd);
	free(pars->path);
	exit(127);
}

int	new_proccess(t_pars *pars, t_env *env)
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
		execute_cmd(pars, env);
	}
	if (pars->cmd != NULL)
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("error waitpid");
		exit(EXIT_FAILURE);
	}
	init_siagtion(INTERACTIVE);
	return (status);
}

void	run_single_cmd(t_pars *pars, t_i_env *i_env)
{
	int	exit_status;

	if (pars -> cmd != NULL)
	{
		if (access(pars->cmd[0], X_OK | F_OK) == 0)
			pars->path = pars->cmd[0];
	}
	exit_status = new_proccess(pars, i_env->env);
	if (WIFEXITED(exit_status))
	{
		i_env->err_code = WEXITSTATUS(exit_status);
	}
	else
		if(WTERMSIG(exit_status))
			i_env->err_code = g_signal + 128;
}
