/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:09:40 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/27 14:54:21 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_extern_cmd_path(t_pars *pars, t_env *env)
{
	while (pars != NULL)
	{
		if (is_builtin(pars->cmd[0]) == NO_BUILTIN)
		{
			path_hendler(env, &pars, pars->cmd[0]);
		}
		else
		{
			pars->path = NULL;
		}
		pars = pars->next_process;
	}
}
int	run_multi_cmd(t_pars *pars, t_env *env)
 {
	set_extern_cmd_path(pars, env);
	return (1);
}