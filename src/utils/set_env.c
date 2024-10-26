/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:18:51 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/26 19:46:31 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value(char *content)
{
	char *value;
	
	value = ft_strchr(content, '=');
	if (value  == NULL)
		return (NULL);
	else if (*(value + 1) == '\0')
		return (ft_strdup(""));
	else	
		value = ft_strdup(++value);
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
		return (content);
	while(content[i] != '\0')
	{
		if (content[i] == '=')
			break;
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


int	append_node(t_env **head_env, char *content)
{
	t_env	*new_node;
	char	**env_var;

	env_var  = ft_split(content, '=');
	if (env_var == NULL)
		return (0);
	if (env_var[1] == NULL)
	{
		return (0);
	}
	new_node = ft_env_lstnew(env_var[0], env_var[1]);
	if (new_node == NULL)
		return (0);
	if (*head_env == NULL)
		*head_env = new_node; 
	else
		ll_addback(head_env, new_node);
	return (1);
}


int	update_env_value(t_env *env, char *var_name, char *new_val)
{
	while (env != NULL)
	{
		if (!ft_strncmp(var_name, env->name, ft_strlen(var_name)))
		{
			if (env->value != NULL)
				free(env->value);
			env->value = ft_strdup(new_val);
			if (env->value == NULL)
				return (0);
			return (1);
		}
		env = env->next;
	}
	return 0;
}

char	*key_val_join(char *key, char *value)
{
	char	*tmp;
	char	*full_str;
	
	tmp= ft_strjoin(key, "=");
	if (tmp == NULL)
		return (NULL);
	if (value == NULL)
		full_str = ft_strjoin(tmp, ft_strdup(""));
	else
		full_str = ft_strjoin(tmp, value);
	free(tmp);
	return (full_str);
}

/*This function turns  our environment back into a double array.
To do : during copying nodes into a double array, we MUST free the node we are copying values from */
char **back_to_array(t_env *env)
{
	char	**ptr_env;
	int		size;
	int		count;
	
	count = 0;
	size = ft_lst_size(env);
	ptr_env= ft_calloc(size + 1, sizeof(char *));
	while (env != NULL)
	{
		ptr_env[count] = env->content;
		count++;
		env = env->next;
	}
	return (ptr_env);
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
			return (NULL);
		i++;
	}
	return (head_env);
}