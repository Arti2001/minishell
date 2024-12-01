/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:35:55 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/30 04:49:36 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(tmp->name)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	**env_split_path(t_env **env)
{
	char	*path;

	path = get_path("PATH", *env);
	if (path == NULL)
		return (NULL);
	path = ft_strchr(path, '/');
	return (ft_split(path, ':'));
}

static char	*matching_pathes(char **splited_pathes, char *check_path, t_i_env *i_env)
{
	int		i;
	char	*tmp_path;
	char	*correct_path;

	i = 0;
	i_env->err_code= 0;
	tmp_path = NULL;
	if (splited_pathes == NULL)
		return (NULL);
	while (splited_pathes[i])
	{
		tmp_path = ft_strjoin(splited_pathes[i], "/");
		correct_path = ft_strjoin(tmp_path, check_path);
		if (access(correct_path, X_OK | F_OK) == 0)
			return (free(tmp_path), correct_path);
		i++;
		free (tmp_path);
		free(correct_path);
	}
	return (NULL);
}

char	*is_absolute_executable(char *cmd, t_i_env *i_env)
{
	char	*exec_str;

	exec_str = NULL;
	if (get_path("PATH", i_env->env) == NULL)
	{
		exec_str = ft_strjoin("./", cmd);
		if (exec_str == NULL)
		{
			return (NULL);
		}
		if (access(exec_str, X_OK | F_OK) == 0)
		{
			return (exec_str);
		}
		else
		{
			free(exec_str);
			perror(cmd);
			i_env->err_code = 126;
		}
	}
	return (NULL);
}

void	path_hendler(t_i_env *i_env, t_pars **pars, char *cmd)
{
	char	**splited_pathes;

	splited_pathes = env_split_path(&i_env->env);
	(*pars)->path = matching_pathes(splited_pathes, cmd, i_env);
	double_array_free(splited_pathes);
	if ((*pars)->path != NULL)
		return ;
	(*pars)->path = is_absolute_executable(cmd, i_env);
	if ((*pars)->path != NULL)
		return ;
	if (access(cmd, X_OK | F_OK) == 0)
	{
		(*pars)->path = cmd;
	}
}
