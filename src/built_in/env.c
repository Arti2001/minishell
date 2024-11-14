/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 18:19:28 by amysiv        #+#    #+#                 */
/*   Updated: 2024/11/14 14:29:45 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			printf("%s=%s\n", env->name, env->value);
		}
		env = env->next;
	}
	return (0);
}