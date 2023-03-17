/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:31:23 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/17 19:06:26 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_ceiling_and_floor(t_cube *data, int i)
{
	int	half;
	int	start;

	start = 0;
	half = (data->height - start) / 2;
	while (start < data->height)
	{
		if (start > half)
			mlx_put_pixel(data->img, i, start, data->textures->ceiling->rgb);
		else
			mlx_put_pixel(data->img, i, start, data->textures->floor->rgb);
		start++;
	}
}

void	fill_texture(t_draw_info *info, t_cube *data)
{
	if (data->p.side == NORTH)
		info->tex = data->textures->no_tex;
	if (data->p.side == WEST)
		info->tex = data->textures->we_tex;
	if (data->p.side == SOUTH)
		info->tex = data->textures->so_tex;
	if (data->p.side == EAST)
		info->tex = data->textures->ea_tex;
}

void	fill_info(t_draw_info *info, t_cube *data, double height)
{
	fill_texture(info, data);
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
	draw_ceiling_and_floor(data, i);
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
