/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_cube.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 14:42:51 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/17 16:39:26 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clean_map(t_map *map)
{
	if (map->raw_map)
		free(map->raw_map);
	if (map->map_data)
		free_double_array(map->map_data);
	if (map->start_pos)
		free(map->start_pos);
	free(map);
	return ;
}

void	clean_textures(t_texture *texture)
{
	if (texture->no_tex)
		free(texture->no_tex);
	if (texture->so_tex)
		free(texture->so_tex);
	if (texture->we_tex)
		free(texture->we_tex);
	if (texture->ea_tex)
		free(texture->ea_tex);
	if (texture->ceiling)
		free(texture->ceiling);
	if (texture->floor)
		free(texture->floor);
	free(texture);
	return ;
}

void	clean_cube(t_cube *cube)
{
	if (cube)
	{
		if (cube->map)
			clean_map(cube->map);
		if (cube->textures)
			clean_textures(cube->textures);
		free(cube);
	}
	return ;
}

void	put_error(t_cube *cube, char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (str)
		ft_putstr_fd(str, 2);
	clean_cube(cube);
	exit(EXIT_FAILURE);
}
