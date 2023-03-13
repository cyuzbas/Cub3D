/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 12:21:18 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/12 20:13:53 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

char	*ft_strjoin2(char *s1, char *s2)
{
	char		*str;
	size_t		i;

	if (!s1)
		s1 = (char *)ft_calloc(sizeof(char), 1);
	if (!s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	free(s1);
	return (str);
}

char	*update_container(char	*container)
{
	int		i;
	int		j;
	char	*updated;

	i = 0;
	while (container[i] && container[i] != '\n')
		i++;
	if (!container[i])
	{
		free(container);
		return (NULL);
	}
	updated = (char *)ft_calloc(sizeof(char), (ft_strlen(container) - i + 1));
	j = 0;
	i++;
	while (container[i] && updated)
	{
		updated[j] = container[i];
		j++;
		i++;
	}
	free (container);
	return (updated);
}

char	*get_line(char *container)
{
	int		i;
	char	*get_line;

	i = 0;
	if (!container[i])
		return (NULL);
	while (container[i] && container[i] != '\n')
		i++;
	get_line = (char *)ft_calloc(sizeof(char), (i + 2));
	if (!get_line)
		return (NULL);
	i = 0;
	while (container[i] && container[i] != '\n')
	{
		get_line[i] = container[i];
		i++;
	}
	if (container[i] == '\n')
		get_line[i] = '\n';
	return (get_line);
}

char	*ft_read(char *container, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		check_read;

	check_read = 1;
	while (check_read != 0 && !ft_strchr(container, '\n'))
	{
		check_read = read(fd, buffer, BUFFER_SIZE);
		if (check_read < 0)
		{
			free(container);
			return (NULL);
		}
		buffer[check_read] = '\0';
		container = ft_strjoin2(container, buffer);
		if (container == NULL)
			check_read = 0;
	}
	return (container);
}

char	*get_next_line(int fd)
{
	static char	*container;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1025)
		return (NULL);
	container = ft_read(container, fd);
	if (container == NULL)
	{
		write(1, "read nothing\n", 14);
		return ((char *)-1);
	}
	line = get_line(container);
	container = update_container(container);
	if (line == NULL)
	{
		free (container);
		return (NULL);
	}
	return (line);
}
