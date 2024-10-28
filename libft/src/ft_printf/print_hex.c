/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_hex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 14:23:36 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/12 22:48:51 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_hex_len(t_hex num)
{
	int	len;

	len = 0;
	while (num)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	put_hex(t_hex num, const char format)
{
	if (num >= 16)
	{
		put_hex(num / 16, format);
		put_hex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (format == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
			else
				ft_putchar_fd((num - 10 + 'a'), 1);
		}
	}
}

int	print_hex(t_data *data, va_list *args)
{
	unsigned int	num;

	num = va_arg(*args, unsigned int);
	if (num == 0)
		return (ft_putchar_fd('0', 1), 1);
	else
		put_hex(num, *data->fmt);
	return (get_hex_len(num));
}
