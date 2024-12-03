/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:14:08 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 17:55:16 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	int_check(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '+' || str [0] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

static int	check_err(char **arg)
{
	long	val;

	if (int_check(arg[1]) == 0)
	{
		shell_putendl_fd("exit", 2);
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		shell_putendl_fd(": numeric argument required", 2);
		return (2);
	}
	else if (arg[2] != NULL)
	{
		shell_putendl_fd("exit: too many arguments\n", 2);
		return (1);
	}
	val = ft_atol(arg[1]);
	if (val > INT_MAX || val < INT_MIN)
	{
		shell_putendl_fd("exit", 2);
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		shell_putendl_fd(": numeric argument required", 2);
		return (2);
	}
	return (val % 256);
}

int	ft_exit(char **arg, t_i_env *i_env, t_pars *pars)
{
	long	ret;

	if (arg[1] == NULL)
	{
		exit (i_env->err_code);
	}
	else
	{
		ret = check_err(arg);
	}
	i_env->err_code = ret;
	free_pars(pars);
	rl_clear_history();
	free_list(i_env->env);
	free(i_env);
	exit(ret);
}
