/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_ptr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 14:08:32 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/12 22:48:04 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_ptr(t_data *data, va_list *args)
{
	t_hex	ptr;
	int		print_length;

	ptr = va_arg(*args, t_hex);
	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		print_length = 5;
	}
	else
	{
		ft_putstr_fd("0x", 1);
		print_length = 2;
		put_hex(ptr, *data->fmt);
		print_length += get_hex_len(ptr);
	}
	return (print_length);
}
