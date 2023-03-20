/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 12:41:59 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/20 15:16:01 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= image->width || x < 0)
		return ;
	if (y >= image->height || y < 0)
		return ;
	mlx_put_pixel(image, x, y, color);
}

void	draw_direction(t_cube *cube, int off[2], double angle, int size)
{
	t_map	*map;
	double	pos[2];
	double	x1;
	double	y1;
	int		i;

	map = cube->map;
	i = 0;
	while (i < size)
	{
		pos[0] = cube->p.x * cube->mini.block_size[1];
		pos[1] = cube->p.y * cube->mini.block_size[1];
		x1 = (i * cos((angle))) + pos[0] + 1;
		y1 = (i * sin((angle))) + pos[1] + 1;
		if (x1 < map->col * cube->mini.block_size[1] && x1 > 0 && \
			y1 < map->row * cube->mini.block_size[1] && y1 > 0)
			mlx_put_pixel(cube->img, x1 + off[0], y1 + off[1], RED);
		i++;
	}
}

int	draw_rectangle(int pos[2], int size[2], mlx_image_t *img, char map_element)
{
	int			w;
	int			h;

	w = 0;
	while (w < size[0])
	{
		h = 0;
		while (h < size[1])
		{
			if (map_element == '1')
				put_pixel(img, pos[0] + w, pos[1] - h, WHITE);
			else if (map_element == '0')
				put_pixel(img, pos[0] + w, pos[1] - h, BLACK);
			else if (map_element == ' ')
				put_pixel(img, pos[0] + w, pos[1] - h, GREY);
			else if (map_element == 'P')
				put_pixel(img, pos[0] + w, pos[1] + h, RED);
			else
				put_pixel(img, pos[0] + w, pos[1] - h, BLACK);
			h++;
		}
		w++;
	}
	return (0);
}

void	draw_player(t_cube *c)
{
	int		size[2];
	int		pos[2];
	int		off[2];
	double	x;
	double	y;

	size[0] = c->mini.player_size;
	size[1] = c->mini.player_size;
	x = c->p.x;
	y = c->p.y;
	off[0] = 0;
	off[1] = c->img->height - ((c->mini.block_size[1]) * (c->map->row + 1));
	pos[0] = off[0] + (x * c->mini.block_size[0]);
	pos[1] = off[1] + (y * c->mini.block_size[0]);
	while (c->p.x > x - size[0])
	{
		y = c->p.y;
		while (y - size[1] < c->p.y)
		{
			draw_rectangle(pos, size, c->img, 'P');
			y++;
		}
		x++;
	}
	draw_direction(c, off, c->p.pa, 10);
}

void	draw_minimap(t_cube *cube, mlx_image_t *img)
{
	int			x;
	int			y;
	int			pos[2];

	y = 0;
	while (y < cube->map->row)
	{
		x = 0;
		while (x < cube->map->col)
		{
			pos[0] = x * (int)(cube->mini.block_size[0]);
			pos[1] = img->height - ((cube->mini.block_size[1]) * \
				cube->map->row) + (y * (int)(cube->mini.block_size[1]));
			draw_rectangle(pos, cube->mini.block_size, \
			img, cube->map->map_data[y][x]);
			x++;
		}
		y++;
	}
	draw_player(cube);
}
