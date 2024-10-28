/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/27 14:13:23 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/12 22:49:27 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	init_data(t_data **data, const char *fmt)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (-1);
	(*data)->fmt = (char *)fmt;
	(*data)->print_length = 0;
	(*data)->error = false;
	return (0);
}

void	print_proceed(t_data *data, va_list *args)
{
	if (*data->fmt == '%')
	{
		data->fmt++;
		data->print_length += call_handler(data, args);
	}
	else
	{
		ft_putchar_fd(*data->fmt, 1);
		data->print_length++;
	}
	data->fmt++;
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	t_data	*data;
	int		printed;

	va_start(args, fmt);
	if (init_data(&data, fmt) != 0)
		return (-1);
	while (*data->fmt)
	{
		print_proceed(data, &args);
		if (data->error)
			return (-1);
	}
	printed = data->print_length;
	free(data);
	va_end(args);
	return (printed);
}
