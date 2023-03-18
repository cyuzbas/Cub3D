/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:53:08 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/18 17:38:32 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_alg(t_cube *data, t_calculation *ca)
{
	while (ca->hit == 0)
	{
		if (ca->side_x < ca->side_y)
		{
			ca->side_x += ca->delta_x;
			ca->map_x += ca->step_x;
			data->p.side = 0 + (ca->step_x + 1);
		}
		else
		{
			ca->side_y += ca->delta_y;
			ca->map_y += ca->step_y;
			data->p.side = 1 + (1 + ca->step_y);
		}
		if (data->map->map_data[ca->map_y][ca->map_x] == '1')
			ca->hit = 1;
	}
}

void	find_ray(t_calculation *cal, t_cube *data)
{
	if (cal->ray_x < 0)
	{
		cal->step_x = -1;
		cal->side_x = (data->p.x - cal->map_x) * cal->delta_x;
	}
	else
	{
		cal->step_x = 1;
		cal->side_x = (cal->map_x + 1.0 - data->p.x) * cal->delta_x;
	}
	if (cal->ray_y < 0)
	{
		cal->step_y = -1;
		cal->side_y = (data->p.y - cal->map_y) * cal->delta_y;
	}
	else
	{
		cal->step_y = 1;
		cal->side_y = (cal->map_y + 1.0 - data->p.y) * cal->delta_y;
	}
}

double	perp_distance(t_cube *data, t_calculation *cal, double angle)
{
	double	distance;
	double	ca;
	double	perp_dist;

	if (data->p.side == 0 || data->p.side == 2)
		distance = cal->side_x - cal->delta_x;
	else
		distance = cal->side_y - cal->delta_y;
	ca = data->p.pa - angle;
	if (ca < 0)
		ca += 2 * M_PI;
	else if (ca > 2 * M_PI)
		ca -= 2 * M_PI;
	perp_dist = distance * cos(ca);
	perp_dist = fabs(perp_dist);
	if (data->p.side == EAST || data->p.side == WEST)
		data->p.wall_x = data->p.y + cal->ray_y * perp_dist;
	else
		data->p.wall_x = data->p.x + cal->ray_x * perp_dist;
	data->p.wall_x -= floorf(data->p.wall_x);
	return (perp_dist);
}

double	len_find(t_cube *data, double angle)
{
	t_calculation	cal;

	cal.map_y = data->map->start_pos->y;
	cal.map_x = data->map->start_pos->x;
	cal.ray_x = cos(angle);
	cal.ray_y = sin(angle);
	cal.hit = 0;
	if (cal.ray_x == 0)
		cal.ray_x = 1e30;
	else
		cal.delta_x = fabs(1 / cal.ray_x);
	if (cal.ray_y == 0)
		cal.ray_y = 1e30;
	else
		cal.delta_y = fabs(1 / cal.ray_y);
	find_ray(&cal, data);
	dda_alg(data, &cal);
	return (perp_distance(data, &cal, angle));
}

void	draw_3d_map(t_cube *data)
{
	int		a;
	double	i;

	i = -0.3;
	a = 0;
	while (i < 0.3)
	{
		data->p.ray = len_find(data, data->p.pa + i);
		walls(data, a);
		i += 0.0006;
		a++;
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}
