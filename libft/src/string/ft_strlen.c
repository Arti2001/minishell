/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:32:13 by ydidenko          #+#    #+#             */
/*   Updated: 2024/10/28 14:28:46 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

/*
** The strlen() function calculates the length of the string pointed to by s,
** excluding the terminating null byte ('\0').
*/
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}
