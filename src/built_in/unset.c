/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 13:58:32 by amysiv        #+#    #+#                 */
/*   Updated: 2024/11/07 14:29:24 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_unset(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*current;

	if (!env || !(*env))
		return (0);
	tmp = NULL;
	if (ft_strncmp(str, (*env)->name, ft_strlen((*env)->name)) == 0)
	{
		tmp = (*env)->next;
		free_node(*env);
		(*env) = tmp;
		return (1);
	}
	current = *env;
	while(current->next != NULL)
	{
		if (ft_strncmp(str, current->next->name, ft_strlen(current->next->name)) == 0)
		{
			tmp = current->next->next;
			free_node(current->next);
			current->next = tmp;
			return (1);
		}
		current = current->next;
	}
	return (0);
}


int	ft_unset(t_env **env, char **arg)
{
	int	i;

	i = 1;
	if (arg[i] == NULL)
	{
		return (0);
	}
	while (arg[i])
	{
		find_unset(env, arg[i]);
		i++;
	}
	return (0);
}