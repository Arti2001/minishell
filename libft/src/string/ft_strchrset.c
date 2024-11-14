/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchrset.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/07 10:16:33 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/11/07 10:16:35 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrset(const char *s, const char *set)
{
	while (*s)
	{
		if (ft_strrchr(set, *s))
			return ((char *)s);
		s++;
	}
	return (NULL);
}
