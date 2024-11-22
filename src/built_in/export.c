/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:55:48 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/23 00:03:17 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_syntax(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[0]) && !(str[0] == '_'))
	{
		ft_putstr_fd("bash: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	while (str[i])
	{
		if (ft_isalpha(str[i]) || (str[i] == '_') || ft_isdigit(str[i]))
			i++;
		else
		{
			ft_putstr_fd("bash: export: '", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
	}
	return (0);
}

int	key_exists(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (!ft_strncmp(key, env->name, ft_strlen(key) + 1))
		{
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static int	print_export_env(t_env *env)
{
	if (env == NULL)
	{
		return (1);
	}
	while (env != NULL)
	{
		if (env->value == NULL)
		{
			printf("declare -x %s\n", env->name);
		}
		else
		{
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		}
		env = env->next;
	}
	return (0);
}

int	insert_or_assign(t_env *env, char *key, char *value)
{
	t_env	*new_node;

	if (key_exists(env, key))
	{
		return (update_env_value(env, key, value));
	}
	else
	{
		new_node = ft_env_lstnew(key, value);
		if (new_node == NULL)
		{
			return (1);
		}
		ll_addback(&env, new_node);
	}
	return (0);
}

int	ft_export(t_env *env, char **commands)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	if (commands[i] == NULL)
		return (print_export_env(env));
	while (commands[i] != NULL)
	{
		key = get_key(commands[i]);
		value = get_value(commands[i]);
		if (key == NULL)
			return (free(value), 1);
		if (check_var_syntax(key))
			return (free_key_value(key, value), 1);
		if (insert_or_assign(env, key, value))
			return (free_key_value(key, value), 1);
		free_key_value(key, value);
		i++;
	}
	return (0);
}
