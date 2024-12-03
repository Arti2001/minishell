/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:38:10 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 18:09:59 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_array_free(char **to_free)
{
	int	i;

	i = 0;
	if (to_free == NULL)
		return ;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	to_free = NULL;
}

void	free_node(t_env *node)
{
	if (node)
	{
		if (node->content)
			free(node->content);
		if (node->name)
			free(node->name);
		if (node->value)
			free(node->value);
		free(node);
	}
}
void	free_list(t_env *env)
{
	t_env *tmp;

	while (env != NULL) {
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp->content);
		free(tmp);
	}
}

void	free_key_value(char *key, char *value)
{
	free(key);
	key = NULL;
	free(value);
	value = NULL;
}