/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 14:35:17 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/13 15:54:36 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	put_error(t_cube *cube, char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (str)
		ft_putstr_fd(str, 2);
	// clean_cube(cube);
	if (cube)
		free(cube);
	exit(EXIT_FAILURE);
}