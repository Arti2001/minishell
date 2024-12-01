/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:16:30 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/30 02:13:29 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_cwd(t_env *env, char *str)
{
	char	*curr;

	curr = getcwd(NULL, 0);
	update_env_value(env, "OLDPWD", curr);
	free(curr);
	chdir(str);
	curr = getcwd(NULL, 0);
	update_env_value(env, "PWD", curr);
	free(curr);
	return (0);
}

static int	change_to_home(t_env *env)
{
	char	*home;

	home = get_path("HOME", env);
	if (home == NULL)
	{
		shell_putendl_fd("bash: cd: HOME not set", 2);
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
		return (closedir(dir), change_cwd(env, arg[1]));
	}
	else if (access(arg[1], F_OK) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(arg[1], 2);
		shell_putendl_fd(": No such file or directory", 2);
		return (closedir(dir), 1);
	}
	else if (dir == NULL)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(arg[1], 2);
		shell_putendl_fd(" Not a directory", 2);
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
		shell_putendl_fd("bash: cd: too many arguments", 2);
		return (1);
	}
	else
		return (cd_check(arg, env));
}
