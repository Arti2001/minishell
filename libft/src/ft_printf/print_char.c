/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_char.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 18:31:54 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/12 22:49:00 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(t_data *data, va_list *args)
{
	char	c;

	(void)data;
	c = (char)va_arg(*args, int);
	return (ft_putchar_fd((char)c, 1), 1);
}
