/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:17:34 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/23 00:00:44 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_new_line(char *str)
{
	if ((*(str + 0) == '-') && (*(str + 1) == 'n'))
	{
		str++;
	}
	while (*str)
	{
		if (*(str + 0) == 'n')
		{
			str++;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}

static void	basic_echo(char **commands)
{
	int	i;

	i = 1;
	while (commands[i])
	{
		if ((commands[i + 1]) != NULL)
		{
			ft_putstr_fd(commands[i], 1);
			write(1, " ", 1);
		}
		else
		{
			ft_putendl_fd(commands[i], 1);
		}
		i++;
	}
}

int	ft_echo(char **commands)
{
	int	i;

	i = 1;
	if (commands[i] == NULL)
	{
		return (ft_putstr_fd("\n", 1), 0);
	}
	else if (check_new_line(commands[i]))
	{
		i = 2;
		while (commands[i])
		{
			ft_putstr_fd(commands[i], 1);
			if ((commands[i + 1]) != NULL)
			{
				write(1, " ", 1);
			}
			i++;
		}
	}
	else
		basic_echo(commands);
	return (0);
}
