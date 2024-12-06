/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:56:16 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/06 14:11:06 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

int	inner(t_i_env *i_env, t_pars *pars, int *ret, char *input)
{
	input = readline("minishell$ ");
	if (input == NULL)
	{
		printf("exit\n");
		return (1);
	}
	if (!input[0])
	{
		free(input);
		return (2);
	}
	if (g_signal == 2)
		i_env->err_code = 130;
	add_history(input);
	pars = init_pars(input, i_env);
	free(input);
	if (pars == NULL)
	{
		*ret = i_env->err_code;
		return (2);
	}
	*ret = execution(pars, i_env);
	g_signal = 0;
	free_pars(pars);
	return (0);
}

void	loop(t_i_env *i_env, t_pars *pars, int *ret)
{
	char	*input;
	int		status;

	input = NULL;
	while (1)
	{
		status = inner(i_env, pars, ret, input);
		if (status == 1)
			break ;
		if (status == 2)
			continue ;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pars	*pars;
	t_i_env	*i_env;
	int		ret;

	ret = 0;
	pars = NULL;
	if (check_fd())
		return (shell_putendl_fd("mshell: forbidden", 2), 1);
	if (argc == 1 && argv[0])
	{
		i_env = (t_i_env *)null_exit(malloc(sizeof(t_i_env)));
		i_env->err_code = 0;
		i_env->env = (t_env *)null_exit(set_env(envp));
		if (i_env->env == NULL)
			return (free(i_env), 1);
		shell_lvl(i_env->env);
		g_signal = 0;
		init_sigaction(INTERACTIVE);
		loop(i_env, pars, &ret);
		rl_clear_history();
		free_list(i_env->env);
		free(i_env);
	}
	return (ret);
}
