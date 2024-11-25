/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:58:32 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/25 18:32:16 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_firs_node(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = NULL;
	if (ft_strncmp(str, (*env)->name, ft_strlen((*env)->name) + 1) == 0)
	{
		tmp = (*env)->next;
		free_node(*env);
		*env = tmp;
		return (0);
	}
	return (1);
}

int	find_unset(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*curr;

	tmp = NULL;
	curr = *env;
	if (!env || !(env))
		return (0);
	if (!unset_firs_node(env, str))
		return (0);
	while (curr->next != NULL)
	{
		if (ft_strncmp(str, curr->next->name, \
			ft_strlen(curr->next->name) + 1) == 0)
		{
			tmp = curr->next->next;
			free_node(curr->next);
			curr->next = tmp;
			return (0);
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_unset(t_env **env, char **arg)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (arg[i] == NULL)
	{
		return (0);
	}
	while (arg[i])
	{
		ret = find_unset(env, arg[i]);
		i++;
	}
	return (ret);
}
