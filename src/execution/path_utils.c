/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:35:55 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 21:03:14 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_split_path(t_env **env)
{
	char	*path;
	char	**splited;

	splited = NULL;
	path = get_path("PATH", *env);
	if (path == NULL)
		return (NULL);
	path = ft_strchr(path, '/');
	splited = ft_split(path, ':');
	if (splited == NULL)
		return (NULL);
	return (splited);
}

char	*path_checks(char *check_path, t_i_env *i_env)
{
	if (access(check_path, X_OK | F_OK) == 0)
		return (check_path);
	else if (errno == EACCES)
	{
		perror(check_path);
		i_env->err_code = errno;
	}
	else
		return (check_path);
	return (NULL);
}

char	*path_is_set(char **splited_pathes, char *check_path, t_i_env *i_env)
{
	int		i;
	char	*tmp_path;
	char	*correct_path;

	i = 0;
	tmp_path = NULL;
	correct_path = NULL;
	while (splited_pathes[i] != NULL && check_path[0] != '.')
	{
		tmp_path = ft_strjoin(splited_pathes[i], "/");
		correct_path = ft_strjoin(tmp_path, check_path);
		if (access(correct_path, X_OK | F_OK) == 0)
			return (free(tmp_path), correct_path);
		i++;
		free (tmp_path);
		free(correct_path);
	}
	return (path_checks(check_path, i_env));
}

char	*path_is_unset(char *cmd, t_i_env *i_env)
{
	if (access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	else
		perror(cmd);
	i_env->err_code = errno;
	return (NULL);
}

void	path_handler(char *cmd, t_i_env *i_env, t_pars **pars)
{
	char	**pathes;

	pathes = env_split_path(&i_env->env);
	if (pathes == NULL || pathes[0] == NULL)
	{
		(*pars)->path = path_is_unset(cmd, i_env);
	}
	else
	{
		(*pars)->path = path_is_set(pathes, cmd, i_env);
	}
	if (pathes)
		double_array_free(pathes);
}
