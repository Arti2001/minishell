/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:35:55 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/27 12:13:38 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	*get_path(char *name, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
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
;	path = ft_strchr(path, '/');
	return (ft_split(path, ':'));
}

void	matching_pathes(t_exec *holds, char *check_path)
{
	int		i;

	i = 0;
	if (holds->all_pathes == NULL)
		return ;
	while (holds->all_pathes[i])
	{
		holds->temp_path = ft_strjoin(holds->all_pathes[i], "/");
		holds->true_path = ft_strjoin(holds->temp_path, check_path);
		if (access(holds->true_path, X_OK | F_OK) == 0)
		{
			free(holds->temp_path);
			return ;
		}
			i++;
			free (holds->temp_path);
	}
}