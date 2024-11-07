/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eugenedidenko <eugenedidenko@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 20:47:15 by eugenediden   #+#    #+#                 */
/*   Updated: 2024/11/07 14:29:24 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*null_exit(void	*ptr)
{
	if (ptr != NULL)
		return (ptr);
	perror("minishell");
	exit(1);
}

