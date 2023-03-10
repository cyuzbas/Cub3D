/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_cube.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/12 20:01:29 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/12 20:14:06 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_colour(t_colour *colour)
{
	colour = (t_colour *)malloc(sizeof(t_colour));
	colour->rgb = 0;
	colour->r = 0;
	colour->g = 0;
	colour->b = 0;
}

void	init_texture(t_texture *textures)
{
	textures->count = 0;
	textures->no_tex = NULL;
	textures->so_tex = NULL;
	textures->we_tex = NULL;
	textures->ea_tex = NULL;
	textures->ceiling = (t_colour *)malloc(sizeof(t_colour));
	init_colour(textures->ceiling);
	textures->floor = (t_colour *)malloc(sizeof(t_colour));
	init_colour(textures->floor);
}

void	init_map(t_map *map)
{
	map->raw_map = NULL;
	map->map_data = NULL;
	map->row = 0;
	map->col = 0;
	map->start_pos = (t_position *)malloc(sizeof(t_position));
	map->start_pos->x = -1;
	map->start_pos->y = -1;
	map->start_pos->dir = 0;
}

int	init_cube(t_cube *cube)
{
	cube->map = (t_map *)malloc(sizeof(t_map));
	init_map(cube->map);
	cube->textures = (t_texture *)malloc(sizeof(t_texture));
	init_texture(cube->textures);
	return (0);
}
