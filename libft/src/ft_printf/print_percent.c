/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_percent.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 18:31:57 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/12 22:47:53 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_percent(t_data *data, va_list *args)
{
	(void)args;
	(void)data;
	return (ft_putchar_fd('%', 1), 1);
}
