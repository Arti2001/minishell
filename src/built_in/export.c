/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:55:48 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/26 19:38:33 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_var_syntax(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[0]) && !(str[0] == '_'))
	{
		printf("bash: export: '%s': not a valid identifier\n", str);
		return (0);
	}
	while(str[i])
	{
		if (ft_isalpha(str[i])|| (str[i] == '_') || ft_isdigit(str[i]))
		{
			i++;
		}
		else
		{
			printf("bash: export: '%s': not a valid identifier\n", str);
			return (0);
		}
	}
	return (1);
}

int	check_equel(char *str)
{
	while (*str)
	{
		if (*(str + 0) == '=')
		{
			return (1);
		}
		str++;
	}
	return (0);
}


int	key_exists(t_env *env, char *key)
{
	while (env != NULL)
	{
		size_t len_key;
		size_t len_current_key;
		
		len_current_key = ft_strlen(env->name);
		len_key = ft_strlen(key);
		if (len_key == len_current_key && !ft_strncmp(key, env->name, len_key)) 
		{
			return (1);
		}
		env = env->next;
	}
	return (0);
}


void	print_export_env(t_env *env)
{
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
	return ;
}

int	insert_or_assign(t_env* env, char *key, char *value)
{
	t_env	*new_node;
	
	if (key_exists(env, key))
	{
		if (!update_env_value(env, key, value))
			return (0);
	}
	else
	{
		new_node = ft_env_lstnew(key, value);
		if (new_node == NULL)
		{
			return (0);
		}
		ll_addback(&env, new_node);
	}
	return (1);
}

//int	ft_export(t_env *env, char **commands)
//{
//	int		i;
//	t_env	*new_node;

//	i = 1;
//	if (commands[i] == NULL)
//	{
//		print_export_env(env);
//		return (0);
//	}
//	while (commands[i] != NULL)
//	{
//		if (varchecker(env, commands[i]) == 1)
//		{
//			new_node = ft_env_lstnew(commands[i]);
//			ll_addback(&env, new_node);
//		}
//		i++;
//	}
//	return (0);
//}


int	ft_export(t_env *env, char **commands)
{
	//char	**key_value;
	char	*key;
	char	*value;
	
	int		i;

	i = 1;
	if (commands[i] == NULL)
	{
		print_export_env(env);
		return (0);
	}
	while (commands[i] != NULL)
	{
		//key_value = ft_split(commands[i], '=');
		key = get_key(commands[i]);
		value = get_value(commands[i]);
		if (key == NULL || value == NULL)
		{
			return (0);
		}
		if (!check_var_syntax(key))
		{
			//double_array_free(key_value)
			free(key);
			free(value);
			return (0);
		}
		if (!insert_or_assign(env, key, value))
		{
			free(key);
			free(value);
			return (0);
		}
		i++;
		free(key);
		free(value);
	}
	return (0);
}

