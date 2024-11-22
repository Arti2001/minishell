/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:14:08 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/22 22:41:30 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	int_check(char *str)
{
	int		i;

	i = 0;
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
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (2);
	}
	else if (arg[2] != NULL)
	{
		ft_putendl_fd("exit: too many arguments\n", 2);
		return (1);
	}
	val = ft_atol(arg[1]);
	if (val > INT_MAX || val < INT_MIN)
	{
		ft_putendl_fd("exit", 2);
		return (1);
	}
	return (val % 256);
}

int	ft_exit(char **arg, t_i_env *i_env)
{
	long	ret;

	if (arg[1] == NULL)
	{
		ret = 0;
	}
	else
	{
		ret = check_err(arg);
	}
	i_env->err_code = ret;
	exit(ret);
}
