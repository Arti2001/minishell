/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_nbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 19:49:23 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/12 22:47:40 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_nbr(t_data *data, va_list *args)
{
	int		len;
	int		n;
	char	*num;

	n = va_arg(*args, int);
	num = ft_itoa(n);
	if (!num)
		return (data->error = true, 0);
	len = ft_strlen(num);
	ft_putstr_fd(num, 1);
	return (free(num), len);
}
