/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:31:23 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/15 15:34:19 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../lib/libft/libft.h"
#include <stdlib.h>
#include <math.h>

#include <memory.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "cub3d.h"

typedef struct s_draw_info
{
	int				top;
	int				bottom;
	unsigned int	color;
	double			step;
	mlx_texture_t	*tex;
	double			text_start;
}					t_draw_info;

static int	get_rgba(mlx_texture_t *texture, int x, int y)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = texture->pixels[y * texture->width * 4 + (x * 4)];
	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

// void	draw_ceiling_and_floor(t_cube *data, int i)
// {
// 	int	half;
// 	int	start;

// 	start = 0;
// 	half = (SCREENHEIGHT - start) / 2;
// 	while (start < SCREENHEIGHT)
// 	{
// 		if (start < half)
// 			mlx_put_pixel(data->img, i, start, data->rgb_ceiling);
// 		else
// 			mlx_put_pixel(data->img, i, start, data->rgb_floor);
// 		start++;
// 	}
// }


void	fill_info(t_draw_info *info, t_cube *data, double height)
{
	info->tex = data->textures->no_tex;
	if (height >= data->img->height)
	{
		info->top = 0;
		info->bottom = data->img->height - 1;
		info->text_start = (((1 - (1.0 * data->img->height / height)) / 2.0)
				* info->tex->height);
	}
	else
	{
		info->top = (data->img->height - height) / 2;
		info->bottom = (data->img->height + height) / 2;
		info->text_start = 0.0;
	}
	info->step = 1.0 * info->tex->height / height;
}


void	walls(t_cube *data, int i)
{
	double		height;
	int			x;
	t_draw_info	info;

	height = data->height / data->p.ray;
	x = 0;
	fill_info(&info, data, height);
	// draw_ceiling_and_floor(data, i);
	while (x < info.bottom - info.top)
	{
		if (data->p.side == EAST || data->p.side == NORTH)
			info.color = get_rgba(info.tex,
					((unsigned int)((1.0 - data->p.wall_x)
							* info.tex->width)),
					((unsigned int)(info.text_start + x * info.step)));
		else
			info.color = get_rgba(info.tex,
					((unsigned int)((data->p.wall_x) * info.tex->width)),
					((unsigned int)(info.text_start + x * info.step)));
		mlx_put_pixel(data->img, i, x + info.top, info.color);
		x++;
	}
	i++;
}