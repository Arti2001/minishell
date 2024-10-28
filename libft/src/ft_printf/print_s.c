/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_s.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 18:31:46 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/12 22:48:26 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_s(t_data *data, va_list *args)
{
	char	*str;

	(void)data;
	str = va_arg(*args, char *);
	if (str == NULL)
		return (ft_putstr_fd("(null)", 1), 6);
	return (ft_putstr_fd(str, 1), ft_strlen(str));
}
