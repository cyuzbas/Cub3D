#include "get_next_line.h"

char	*gettheline(char	**tempstr)
{
	int		len;
	char	*retstr;
	char	*rem;

	len = 0;
	while ((*tempstr)[len] != '\n' && (*tempstr)[len] != '\0')
		len++;
	if (ft_strchr(*tempstr, '\n') != 0
		&& (*(ft_strchr(*tempstr, '\n') + 1)) != '\0')
	{
		retstr = ft_substr(*tempstr, 0, len + 1);
		rem = ft_strdup((*tempstr) + len + 1);
		free(*tempstr);
		*tempstr = rem;
	}
	else
	{
		retstr = ft_strdup(*tempstr);
		free(*tempstr);
		*tempstr = NULL;
	}
	return (retstr);
}

char	*real_gnl(char **tempstr, char *buffer, int readlen)
{
	char	*retstr;
	char	*rem;

	if (!readlen)
	{
		rem = ft_strdup(*tempstr);
		free(*tempstr);
		*tempstr = NULL;
		return (rem);
	}
	rem = ft_strjoin(*tempstr, buffer);
	free(*tempstr);
	*tempstr = NULL;
	if (*rem != '\0')
		*tempstr = rem;
	if (ft_strchr(*tempstr, '\n'))
	{
		retstr = gettheline(tempstr);
		return (retstr);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*tempstr;
	char		*retstr;
	int			readlen;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) == -1)
		return (0);
	readlen = 1;
	retstr = NULL;
	if (!ft_strchr(tempstr, '\n'))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (0);
		while (!retstr && readlen > 0)
		{
			readlen = read(fd, buffer, BUFFER_SIZE);
			buffer[readlen] = '\0';
			retstr = real_gnl(&tempstr, buffer, readlen);
		}
		free (buffer);
	}
	else
		retstr = gettheline(&tempstr);
	return (retstr);
}
