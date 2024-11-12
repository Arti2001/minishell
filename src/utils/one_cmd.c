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

#include "../../includes/minishell.h"

/* This function runs small child proccess and executes given command-> */
void	new_proccess(t_pars *pars, t_env *env)
{
	char	**env_array;
	pid_t	pid;

	env_array = back_to_array(env);
	pid = fork();
	if (pid == -1)
	{
		perror("pid filed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(pars->path, pars->cmd, env_array);
		ft_putstr_fd(pars->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		double_array_free(pars->cmd);
		free(pars->path);
		exit(127);
	}
	waitpid(pid, NULL, 0);
}
void duplicate_origin_fd(int *origin_in, int *origin_out)
{
	*origin_in = dup(STDIN_FILENO);
	if (*origin_in == -1)
	{
		perror("failed to dupuplicate the original stdin");
		return ;

	}
	*origin_out = dup(STDOUT_FILENO);
	if (*origin_out == -1)
	{
		perror("failed to dupuplicate the original stdout");
		return ;
	}
}

void	run_single_cmd(t_pars *pars, t_env *env)
{	
	int		orig_in;
	int		orig_out;

	duplicate_origin_fd(&orig_in, &orig_out);
	if (pars->cmd == NULL)
	{
		return ;
	}
	if(pars->redir != NULL)
	{
		run_herdoc(pars->redir);
		redirect_check(pars);
	}
	if (access(pars->cmd[0], X_OK | F_OK) == 0)
	{
		pars->path = pars->cmd[0];
		new_proccess(pars, env);
		return ;
	}
	path_hendler(env, &pars, pars->cmd[0]);
	new_proccess(pars, env);
	if(pars->redir != NULL)
	{
		restore_fd(orig_in, orig_out);
	}
}
