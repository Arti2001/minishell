/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:30:47 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/27 13:29:49 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **arg)
{
	char	*path;

	if (arg[1] != NULL)
	{
		ft_putendl_fd("To many arguments", 2);
		return (1);
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_putendl_fd("Failed to define the current workin directory", 2);
		return (1);
	}
	else
	{
		ft_putendl_fd(path, 1);
		free(path);
		return (0);
	}
	return (0);
}
