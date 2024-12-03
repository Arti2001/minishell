/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:18:51 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 20:07:14 by amysiv           ###   ########.fr       */
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
	if (key == NULL)
		return (NULL);
	key[i--] = '\0';
	while (i >= 0)
	{
		key[i] = content[i];
		i--;
	}
	return (key);
}

static int	append_node(t_env **head_env, char *content)
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