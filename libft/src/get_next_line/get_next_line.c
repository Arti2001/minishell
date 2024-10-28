/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 19:44:27 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/10/12 19:45:09 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cpycat(char *dest, char *src, char *buff)
{
	if (!dest || !src || !buff)
		return (-1);
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	while (*buff)
	{
		*dest = *buff;
		dest++;
		buff++;
	}
	*dest = '\0';
	return (0);
}

char	*append_line(char **dest, char *src)
{
	char	*temp;
	size_t	len;

	if (!*dest)
	{
		*dest = ft_strndup(src, ft_strlen(src));
	}
	else
	{
		len = ft_strlen(*dest) + ft_strlen(src) + 1;
		temp = malloc(sizeof(char) * len);
		if (temp)
		{
			cpycat(temp, *dest, src);
			free(*dest);
			*dest = temp;
		}
	}
	return (*dest);
}

char	*extract_line(char **static_buff)
{
	char	*line;
	char	*newline;
	char	*temp;
	size_t	len;

	newline = ft_strchr(*static_buff, '\n');
	if (newline)
	{
		len = newline - *static_buff + 1;
		line = ft_strndup(*static_buff, len);
		if (*(newline + 1) != '\0')
		{
			temp = ft_strndup(newline + 1, ft_strlen(newline + 1));
			free(*static_buff);
			*static_buff = temp;
		}
		else
		{
			free(*static_buff);
			*static_buff = NULL;
		}
		return (line);
	}
	return (NULL);
}

char	*read_line(int fd, char **static_buff, char **line)
{
	char	*buff;
	int		bytes_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		if (!append_line(static_buff, buff))
			break ;
		*line = extract_line(static_buff);
		if (*line)
			break ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		*line = NULL;
		free(*static_buff);
		*static_buff = NULL;
	}
	free(buff);
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*static_buff = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (read_line(fd, &static_buff, &line))
		return (line);
	else if (!static_buff && !line)
		return (NULL);
	if (static_buff && *static_buff)
	{
		line = extract_line(&static_buff);
		if (!line && *static_buff)
		{
			line = ft_strndup(static_buff, ft_strlen(static_buff));
			free(static_buff);
			static_buff = NULL;
		}
		return (line);
	}
	line = NULL;
	free(static_buff);
	static_buff = NULL;
	return (line);
}
