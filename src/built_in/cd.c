/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:16:30 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/28 19:40:16 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_cwd(t_env *env, char *str)
{
	update_env_value(env, "OLDPWD", getcwd(NULL, 0));
	chdir(str);
	update_env_value(env, "PWD", getcwd(NULL, 0));
}

//void	init_pwd(t_env *env, char *name, char *value)
//{
//	char	*tmp;
//	char	*full_var;
	
//	tmp = ft_strjoin(name, "=");
//	full_var = ft_strjoin(tmp, value);
//	free(tmp);
//	add_var(env, full_var);
//	free(full_var);
//}
int		ft_cd(t_env *env, char **arg)
{
	DIR		*dir;
	char	*home;

	dir = opendir(arg[1]);
	home = get_path("HOME", env);
	if (arg[1] == NULL)
	{
		if (home == NULL)
			return (ft_putendl_fd("bash: cd: HOME not set\n", 2), 1);
		return (change_cwd(env, home), 0);
	}
	else if (arg[2] != NULL)
		return (ft_putendl_fd("bash: cd: too many arguments", 2), 1);
	else if (access(arg[1], F_OK ) == 0 && (dir != NULL))
		return (change_cwd(env, arg[1]), 0);
	else if (access(arg[1], F_OK) == -1)
		return (printf("bash: %s: %s: No such file or directory\n", arg[0], arg[1]), 1);
	else if (dir == NULL)
	{
		
		printf("bash: %s: %s: Not a directory\n", arg[0], arg[1]);
		return (closedir(dir), 1);
	}
	closedir(dir);
	return (0);
}