/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:58:49 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/12 22:49:38 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	call_handler(t_data *data, va_list *args)
{
	static t_handler	handlers[127] = {
	['s'] = print_s, ['%'] = print_percent, ['c'] = print_char,
	['i'] = print_nbr, ['d'] = print_nbr, ['p'] = print_ptr,
	['x'] = print_hex, ['X'] = print_hex, ['u'] = print_unsigned
	};
	int					print_length;
	t_handler			handler;

	print_length = 0;
	handler = handlers[(int)(*data->fmt)];
	if (handler != NULL)
		print_length += handler(data, args);
	else
		print_length += print_unknown(data, args);
	return (print_length);
}
