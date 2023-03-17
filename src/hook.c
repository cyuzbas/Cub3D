/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:31:23 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/17 19:05:12 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_wall(int x, int y, t_cube *data)
{
	if (data->map->col > x && data->map->row > y && x > 0 && y > 0)
	{
		if (data->map->map_data[y][x] == '1')
			return (1);
		return (0);
	}
	return (1);
}

void	move_up_down(t_cube *vars)
{
	mlx_t	*mlx;
	double	move_x;
	double	move_y;

	mlx = vars->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
	{
		move_x = vars->p.x + vars->p.game_speed * cos(vars->p.pa);
		move_y = vars->p.y + vars->p.game_speed * sin(vars->p.pa);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
	{
		move_x = vars->p.x - vars->p.game_speed * cos(vars->p.pa);
		move_y = vars->p.y - vars->p.game_speed * sin(vars->p.pa);
	}
	if (!hit_wall(move_x, move_y, vars))
	{
		vars->p.x = move_x;
		vars->p.y = move_y;
	}
}

void	move_right_left(t_cube *vars)
{
	mlx_t	*mlx;
	double	move_x;
	double	move_y;

	mlx = vars->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		move_x = vars->p.x + vars->p.game_speed * cos(vars->p.pa - 0.5 * M_PI);
		move_y = vars->p.y + vars->p.game_speed * sin(vars->p.pa - 0.5 * M_PI);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		move_x = vars->p.x + vars->p.game_speed * cos(vars->p.pa + 0.5 * M_PI);
		move_y = vars->p.y + vars->p.game_speed * sin(vars->p.pa + 0.5 * M_PI);
	}
	if (!hit_wall(move_x, move_y, vars))
	{
		vars->p.y = move_y;
		vars->p.x = move_x;
	}
}

void	look_right_left(t_cube *vars)
{
	mlx_t	*mlx;

	mlx = vars->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		vars->p.pa -= 0.05 * M_PI;
		if (vars->p.pa < 0)
			vars->p.pa += 2 * M_PI;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		vars->p.pa += 0.05 * M_PI;
		if (vars->p.pa > 2 * M_PI)
			vars->p.pa -= 2 * M_PI;
	}
	vars->p.x_camera = cos(vars->p.pa) * vars->p.game_speed;
	vars->p.y_camera = sin(vars->p.pa) * vars->p.game_speed;
}

void	hook(void *param)
{
	t_cube	*vars;
	mlx_t	*mlx;

	vars = param;
	mlx = vars->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || \
		mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		look_right_left(vars);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W) || \
		mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
		move_up_down(vars);
	if (mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_D))
		move_right_left(vars);
	draw_3d_map(vars);
}
