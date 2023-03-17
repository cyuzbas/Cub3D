/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_cube.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/12 20:01:29 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/17 15:58:07 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_colour(t_colour *colour)
{
	colour->rgb = 0;
	colour->r = 0;
	colour->g = 0;
	colour->b = 0;
}

void	init_texture(t_cube *cube, t_texture *textures)
{
	textures->count = 0;
	textures->no_tex = (mlx_texture_t *)malloc(sizeof(mlx_texture_t));
	textures->so_tex = (mlx_texture_t *)malloc(sizeof(mlx_texture_t));
	textures->we_tex = (mlx_texture_t *)malloc(sizeof(mlx_texture_t));
	textures->ea_tex = (mlx_texture_t *)malloc(sizeof(mlx_texture_t));
	if (!textures->no_tex || !textures->so_tex || \
		!textures->we_tex || !textures->ea_tex)
		put_error(cube, "Failed to initialize the wall texture!\n");
	textures->ceiling = (t_colour *)malloc(sizeof(t_colour));
	if (!textures->ceiling)
		put_error(cube, "Failed to initialize the ceiling colour!\n");
	init_colour(textures->ceiling);
	textures->floor = (t_colour *)malloc(sizeof(t_colour));
	if (!textures->floor)
		put_error(cube, "Failed to initialize the floor colour!\n");
	init_colour(textures->floor);
}

void	init_map(t_cube *cube, t_map *map)
{
	map->raw_map = NULL;
	map->map_data = NULL;
	map->row = 0;
	map->col = 0;
	map->start_pos = (t_position *)malloc(sizeof(t_position));
	if (!map->start_pos)
		put_error(cube, "Failed to initialize the start position!\n");
	map->start_pos->x = -1;
	map->start_pos->y = -1;
	map->start_pos->dir = 0;
}

int	init_cube(t_cube *cube)
{
	cube->map = (t_map *)malloc(sizeof(t_map));
	if (!cube->map)
		put_error(cube, "Failed to initialize the map!\n");
	init_map(cube, cube->map);
	cube->textures = (t_texture *)malloc(sizeof(t_texture));
	if (!cube->textures)
		put_error(cube, "Failed to initialize the texture!\n");
	init_texture(cube, cube->textures);
	return (0);
}
