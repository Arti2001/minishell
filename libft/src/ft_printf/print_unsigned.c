/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_unsigned.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 15:31:13 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/15 11:49:25 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_size(unsigned int number)
{
	unsigned int	length;

	length = 0;
	if (number == 0)
		return (1);
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

/**
 * Allocates (with malloc(3)) and returns a string
 * representing the integer received as an argument.
 * Negative numbers must be handled.
*/
char	*ft_itoa_u(unsigned int number)
{
	char			*string;
	int				length;

	length = get_size(number);
	string = (char *)malloc(sizeof(char) * (length + 1));
	if (string == NULL)
		return (NULL);
	if (number == 0)
		string[0] = '0';
	string[length] = '\0';
	while (number != 0)
	{
		string[length - 1] = (number % 10) + '0';
		number = number / 10;
		length--;
	}
	return (string);
}

int	print_unsigned(t_data *data, va_list *args)
{
	char			*str;
	unsigned int	num;
	int				print_length;

	num = va_arg(*args, unsigned int);
	if (num == 0)
		return (ft_putchar_fd('0', 1), 1);
	else
	{
		str = ft_itoa_u(num);
		if (!str)
			return (data->error = true, 0);
		ft_putstr_fd(str, 1);
	}
	print_length = (int)get_size(num);
	return (free(str), print_length);
}
