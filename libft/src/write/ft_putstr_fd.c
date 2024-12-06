/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 20:48:47 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/12/06 13:45:47 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "libft.h"

/**
 * Outputs the string ’s’ to the given file
 * descriptor.
*/
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s != 0)
	{
		write(fd, &s[i], ft_strlen(s));
		i++;
	}
}
