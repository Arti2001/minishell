/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eugenedidenko <eugenedidenko@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 20:47:15 by eugenediden   #+#    #+#                 */
/*   Updated: 2024/10/28 21:15:14 by eugenediden   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*null_exit(void	*ptr)
{
	if (ptr != NULL)
		return (ptr);
	perror("minishell");
	exit(1);
}

