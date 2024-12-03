/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:56:52 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 20:01:46 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	update_env_value(t_env *env, char *var_name, char *new_val)
{
	while (env != NULL)
	{
		if (!ft_strncmp(var_name, env->name, ft_strlen(var_name) + 1))
		{
			if (new_val == NULL)
			{
				return (0);
			}
			else if (env->value != NULL)
			{
				free(env->value);
			}
			env->value = ft_strdup(new_val);
			free(env->content);
			env->content = key_val_join(env->name, env->value);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

char	**back_to_array(t_env *env)
{
	char	**ptr_env;
	int		size;
	int		count;

	count = 0;
	size = ft_env_size(env);
	ptr_env = ft_calloc(size + 1, sizeof(char *));
	while (env != NULL)
	{
		ptr_env[count] = env->content;
		count++;
		env = env->next;
	}
	return (ptr_env);
}

char	*key_val_join(char *key, char *value)
{
	char	*tmp;
	char	*full_str;
	char	*empty_line;

	empty_line = ft_strdup("");
	tmp= ft_strjoin(key, "=");
	if (tmp == NULL)
		return (free(empty_line), NULL);
	if (value == NULL)
		full_str = ft_strjoin(tmp, empty_line);
	else
		full_str = ft_strjoin(tmp, value);
	free(tmp);
	free(empty_line);
	return (full_str);
}

int	ft_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		env = env->next;
		i++;
	}
	return (i);
}