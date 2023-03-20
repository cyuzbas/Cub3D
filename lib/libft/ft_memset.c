/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 16:57:08 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/17 19:17:52 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, uint32_t c, size_t len)
{
	size_t			leng;
	unsigned char	*p;

	leng = 0;
	p = b;
	while (leng < len)
	{
		*(p + leng) = c;
		leng++;
	}
	return (b);
}
