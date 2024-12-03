/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 19:11:47 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/12/03 19:16:01 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_pars *pars, t_i_env *i_env)
{
	free_pars(pars);
	rl_clear_history();
	free_list(i_env->env);
	free(i_env);
}

int	check_fd(void)
{
	if (!isatty(STDIN_FILENO)
		|| !isatty(STDERR_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	else
		return (0);
}

void	shell_lvl(t_env *env)
{
	char	*value;
	int		shlvl;

	value = get_path("SHLVL", env);
	shlvl = ft_atoi(value);
	shlvl += 1;
	value = ft_itoa(shlvl);
	update_env_value(env, "SHLVL", value);
	free(value);
}
