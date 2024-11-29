/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:30:47 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/29 15:13:36 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_putendl_fd(char *s, int fd)
{
	int	i;
	char	*nl_str;

	
	i = 0;
	nl_str = ft_strjoin(s, "\n");
	if (nl_str == NULL)
		return ;
	if (s != 0)
	{
		write(fd, nl_str, ft_strlen(nl_str));
		i++;
	}
	free(nl_str);
}
int	ft_pwd(char **arg)
{
	char	*path;

	if (arg[1] != NULL)
	{
		shell_putendl_fd("To many arguments", STDERR_FILENO);
		return (1);
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		shell_putendl_fd("Failed to define the current workin directory", \
			STDERR_FILENO);
		return (1);
	}
	else
	{
		shell_putendl_fd(path, STDOUT_FILENO);
		free(path);
		return (0);
	}
	return (0);
}
