/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:18:51 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/30 04:34:40 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *var, t_env *env)
{
	char	*str;
	t_env	*tmp;

	str = NULL;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->name, ft_strlen(var) + 1))
		{
			str = null_exit(ft_strdup(tmp->value));
			break ;
		}
		tmp = tmp->next;
	}
	if (!str)
		str = null_exit(ft_strdup(""));
	return (str);
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

char	*get_value(char *content)
{
	char	*value;

	value = ft_strchr(content, '=');
	if (value == NULL)
	{
		return (NULL);
	}
	else if (*(value + 1) == '\0')
	{
		return (ft_strdup(""));
	}
	else
	{
		value = ft_strdup(++value);
	}
	if (value == NULL)
		return (NULL);
	return (value);
}

char	*get_key(char *content)
{
	int		i;
	char	*key;

	i = 0;
	if (content == NULL)
		return (NULL);
	if (content[i] == '=')
		i++;
	while (content[i] != '\0')
	{
		if (content[i] == '=')
			break ;
		i++;
	}
	key = (char *)malloc(sizeof(char) * (i + 1));
	key[i--] = '\0';
	while (i >= 0)
	{
		key[i] = content[i];
		i--;
	}
	return (key);
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


int	append_node(t_env **head_env, char *content)
{
	char	*key;
	char	*value;
	t_env	*new_node;

	key = get_key(content);
	if (key == NULL)
	{
		return (0);
	}
	value = get_value(content);
	if (value == NULL)
	{
		return (free(key), 0);
	}
	new_node = ft_env_lstnew(key, value);
	if (new_node == NULL)
	{
		return (free(key), free(value), 0);
	}
	if (*head_env == NULL)
		*head_env = new_node;
	else
		ll_addback(head_env, new_node);
	return (free(key), free(value), 1);
}

t_env	*set_env(char **env)
{
	int		i;
	t_env	*head_env;

	i = 0;
	head_env = NULL;
	while (env[i])
	{
		if (!append_node(&head_env, env[i]))
		{
			free_list(head_env);
			return (NULL);
		}
		i++;
	}
	return (head_env);
}