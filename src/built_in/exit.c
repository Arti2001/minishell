/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:14:08 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/27 10:10:16 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	int_chek(char *str)
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
void	ft_exit(char **arg)
{
	long	val;

	if (arg[1] == NULL)
	{
		exit(0);
	}
	else if (int_chek(arg[1]) == 0)
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", arg[1]);
		exit (2);
	}
	else if (arg[2] != NULL)
	{
		printf("exit: too many arguments\n");
		exit (1);
	}
	val= ft_atol(arg[1]);
	if (val > INT_MAX || val < INT_MIN)
	{
		printf("exit\n");
		exit (1);
	}
	val= val % 256;
	exit(val);
}
