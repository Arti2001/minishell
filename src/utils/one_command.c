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
void	new_proccess(t_pars *pars, t_env *env, t_exec	*execute)
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
		execve(execute->true_path, pars->cmd, env_array);
		ft_putstr_fd(pars->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		double_array_free(pars->cmd);
		free(execute->true_path);
		exit(127);
	}
	waitpid(pid, NULL, 0);
	
}

void	run_command(t_pars *pars, t_env *env)
{
	t_exec holds;

	if (pars->cmd == NULL)
		return ;
	if(pars->redir != NULL)
		redirect_check(pars);
	if (access(pars->cmd[0], X_OK | F_OK) == 0)
	{
		holds.true_path = pars->cmd[0];
		new_proccess(pars, env, &holds);
		return ;
	}
	holds.all_pathes = env_split_path(&env);
	if (holds.all_pathes == NULL)
		holds.true_path = NULL;
	matching_pathes(&holds, pars->cmd[0]);
	double_array_free(holds.all_pathes);
	new_proccess(pars, env,  &holds);
	restore_fd(pars);
}
