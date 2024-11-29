/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:50:03 by ydidenko          #+#    #+#             */
/*   Updated: 2024/11/29 13:04:21 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "libft.h"
/**
 * Outputs the string ’s’ to the given file
 * descriptor, followed by a newline.
*/
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s != 0)
	{
		write(fd, &s[i], ft_strlen(s));
		i++;
		write(fd, "\n", 1);
	}
}
