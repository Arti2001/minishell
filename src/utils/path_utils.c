/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/24 16:35:55 by amysiv        #+#    #+#                 */
/*   Updated: 2024/11/07 14:29:24 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_extern_cmd_path(t_pars *pars, t_env *env)
{
	while (pars != NULL)
	{
		if (is_builtin(pars->cmd[0]) == NO_BUILTIN)
		{
			path_hendler(env, &pars, pars->cmd[0]);
		}
		else
		{
			pars->path = NULL;
		}
		pars = pars->next_process;
	}
}

char	*get_path(char *name, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(env->name)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**env_split_path(t_env **env)
{
	char *path;

	path = get_path("PATH", *env);
	if (path == NULL)
		return (NULL);
	path = ft_strchr(path, '/');
	return (ft_split(path, ':'));
}

char	*matching_pathes(char **splited_pathes, char *check_path)
{
	int		i;
	char	*tmp_path;
	char	*correct_path;

	i = 0;
	tmp_path = NULL;
	if (splited_pathes == NULL)
		return (NULL);
	while (splited_pathes[i])
	{
		tmp_path = ft_strjoin(splited_pathes[i], "/");
		correct_path = ft_strjoin(tmp_path, check_path);
		if (access(correct_path, X_OK | F_OK) == 0)
		{
			free(tmp_path);
			return (correct_path);
		}
		i++;
		free (tmp_path);
	}
	return (NULL);
}

void	path_hendler(t_env *env, t_pars **pars, char *cmd)
{
	char **splited_pathes;
	splited_pathes = env_split_path(&env);
	(*pars)->path = matching_pathes(splited_pathes, cmd);
	double_array_free(splited_pathes);
}


