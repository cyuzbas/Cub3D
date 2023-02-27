#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	d;

	if (!s)
		return (0);
	d = (char)c;
	while (*s && *s != d)
		s++;
	if (*s == d)
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	char	*ret;

	if (!s1 && s2)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (0);
	while (*s1)
	{
		ret[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		ret[i] = *s2;
		i++;
		s2++;
	}
	ret[i] = '\0';
	return (ret);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*sub;
	int		i;
	int		slen;

	if (!s)
		return (0);
	if (ft_strlen(s) - start < len)
		slen = ft_strlen(s) - start;
	else
		slen = len;
	sub = malloc((slen + 1) * sizeof(char));
	if (!sub)
		return (0);
	i = 0;
	while (i < slen && start + i < ft_strlen(s))
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dup;

	if (!src)
		return (0);
	i = 0;
	while (src[i])
	{
		i++;
	}
	dup = (char *)malloc(i + 1);
	if (!dup)
		return (0);
	dup[i] = 0;
	while (i > 0)
	{
		i--;
		dup[i] = src[i];
	}
	return (dup);
}
