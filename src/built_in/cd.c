/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:16:30 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/23 00:00:07 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_cwd(t_env *env, char *str)
{
	update_env_value(env, "OLDPWD", getcwd(NULL, 0));
	chdir(str);
	update_env_value(env, "PWD", getcwd(NULL, 0));
	return (0);
}

static int	change_to_home(t_env *env)
{
	char	*home;

	home = get_path("HOME", env);
	if (home == NULL)
	{
		ft_putendl_fd("bash: cd: HOME not set", 2);
		return (1);
	}
	else
		change_cwd(env, home);
	return (0);
}

static int	cd_check(char **arg, t_env *env)
{
	DIR		*dir;

	dir = opendir(arg[1]);
	if (access(arg[1], F_OK) == 0 && (dir != NULL))
	{
		return (change_cwd(env, arg[1]));
	}
	else if (access(arg[1], F_OK) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putendl_fd(" No such file or directory", 2);
		return (closedir(dir), 1);
	}
	else if (dir == NULL)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putendl_fd(" Not a directory", 2);
		return (closedir(dir), 1);
	}
	return (closedir(dir), 1);
}

int	ft_cd(t_env *env, char **arg)
{
	if (arg[1] == NULL)
	{
		return (change_to_home(env));
	}
	else if (arg[2] != NULL)
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		return (1);
	}
	else
		return (cd_check(arg, env));
}
