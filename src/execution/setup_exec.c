/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:30:31 by ydidenko          #+#    #+#             */
/*   Updated: 2024/12/03 21:07:10 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

static void	one_cmd_setup(t_pars *pars, t_i_env *i_env)
{
	if (is_herdoc(pars->redir))
	{
		if (run_herdoc(pars->redir, i_env) == SIGINT)
		{
			i_env->err_code = 128 + g_signal;
			return ;
		}
		else
			i_env->err_code = 0;
	}
	if (pars->cmd != NULL || pars->redir)
	{
		if (pars->cmd && is_builtin(pars->cmd[0]) != NO_BUILTIN)
			i_env->err_code = handle_built_in(pars, i_env);
		else
			i_env->err_code = run_single_cmd(pars, i_env);
	}
}

static void	multi_cmd_setup(t_pars *pars, t_i_env *i_env)
{
	t_pars	*head;

	head = pars;
	if (is_herdoc(pars->redir))
	{
		if (go_all_herdoc(pars, i_env) == SIGINT)
		{
			i_env->err_code = 128 + g_signal;
			return ;
		}
		else
			i_env->err_code = 0;
	}
	if (pars->cmd != NULL)
	{
		i_env->err_code = run_multi_cmd(pars, i_env, head);
	}
}

int	execution(t_pars *pars, t_i_env *i_env)
{
	if (pars->next_process == NULL)
		one_cmd_setup(pars, i_env);
	else
		multi_cmd_setup(pars, i_env);
	return (i_env->err_code);
}
