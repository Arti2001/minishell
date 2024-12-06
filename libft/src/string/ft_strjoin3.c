/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/07 09:53:26 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/12/06 13:45:31 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a new string,
 * which is the result of the concatenation of 's1', 's2' and 's3'.
 */
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	size_t	s1len;
	size_t	s2len;
	size_t	s3len;
	char	*ret;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s3len = ft_strlen(s3);
	ret = malloc(s1len + s2len + s3len + 1);
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, s1, s1len);
	ft_memcpy(ret + s1len, s2, s2len + 1);
	ft_memcpy(ret + s1len + s2len, s3, s3len + 1);
	return (ret);
}
