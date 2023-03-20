/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 13:11:07 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/17 19:17:34 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
