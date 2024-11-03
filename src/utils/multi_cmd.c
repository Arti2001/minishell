/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:09:40 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/27 15:41:30 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_dear_child(int fd[]   , t_pars *pars, t_env *env)
{
	char	**env;

	env = back_to_array(env);
}
int	run_multi_cmd(t_pars *pars, t_env *env)
 {
	pid_t		pid;
	int			fd[2];

	set_extern_cmd_path(pars, env);
	while (pars != NULL)
	{
		if (pipe(fd) == -1)
		{
			perror("Failed to create a pipe in multi cmd");
			return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Failed to fork in multi cmd");
			return (1);
		}
		if (pid == 0)
		{
			my_dear_child(fd, pars, env);
		}
		pars = pars->next_process;
	}
	return (1);
}
