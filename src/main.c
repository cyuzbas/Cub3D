/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */

/*   Created: 2023/03/08 16:11:03 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/15 15:53:56 by cyuzbas       ########   odam.nl         */

/*   Created: 2023/02/27 13:04:11 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/15 15:46:41 by hwang         ########   odam.nl         */

/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../lib/libft/libft.h"
#include <stdlib.h>
#include <math.h>

#include <memory.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../inc/cub3d.h"

void hook(void* param)
{
	t_cube* vars = param;
	mlx_t* mlx = vars->mlx;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);

	// ft_memset(vars->img->pixels,  0, vars->img->width * vars->img->height * sizeof(int));
	// // free(vars->img);
	// // vars->img = mlx_new_image(vars->mlx, vars->width, vars->height);
	
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// {
	// 	// printf("\n LEFT\n--------------------\n");
	// 	// printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
	// 	vars->p.pa -= 0.05 *  M_PI;
	// 	if (vars->p.pa < 0)
	// 		vars->p.pa += 2 * M_PI;
	// 	vars->p.pdx = cos(vars->p.pa) * 5;
	// 	vars->p.pdy = sin(vars->p.pa) * 5;
	// 	// printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// {
	// 	// printf("\n RIGHT\n--------------------\n");
	// 	// printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
	// 	vars->p.pa += 0.05 *  M_PI;
	// 	if (vars->p.pa > 2 * M_PI)
	// 		vars->p.pa -= 2 * M_PI;
	// 	vars->p.pdx = cos(vars->p.pa) * 5;
	// 	vars->p.pdy = sin(vars->p.pa) * 5;
	// 	// printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_UP))
	// {
	// 	// printf("\n UP\n--------------------\n");
		
	// 	// printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
	// 	// vars->p.py -= vars->p.pdy;
	// 	// vars->p.px -= vars->p.pdx;
	// 	vars->p.py += vars->p.pdx;
	// 	vars->p.px += vars->p.pdy;
	// 	// printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
		
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	// {
	// 	// printf("\n DOWN\n--------------------\n");
		
	// 	// printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
	// 	// vars->p.py += vars->p.pdy;
	// 	// vars->p.px += vars->p.pdx;
	// 	vars->p.py -= vars->p.pdx;
	// 	vars->p.px -= vars->p.pdy;
	// 	// printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
		
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_W))
	// {
	// 	vars->p.py += vars->p.pdx;
	// 	vars->p.px += vars->p.pdy;
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_S))
	// {
	// 	vars->p.py -= vars->p.pdx;
	// 	vars->p.px -= vars->p.pdy;
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_A))
	// {
	// 	vars->p.py -= vars->p.pdx;
	// 	vars->p.px += vars->p.pdy;
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_D))
	// {
	// 	vars->p.py += vars->p.pdx;
	// 	vars->p.px -= vars->p.pdy;
	// }
	// draw_2D_map(vars, vars->map->ratio, 1);
}


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
		// printf("mapy %d, mapx%d\n", ca->map_y, ca->map_x);
		// ca->hit = 1;
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

double	find_distance(t_cube *data, t_calculation *cal, double angle)
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

	// printf("%d %d \n",data->map->start_pos->x, data->map->start_pos->y);
	cal.map_y = data->map->start_pos->y;
	cal.map_x = data->map->start_pos->x;
	cal.ray_x = cos(angle);
	cal.ray_y = sin(angle);
	cal.delta_x = fabs(1 / cal.ray_x);
	cal.hit = 0;
	cal.delta_y = fabs(1 / cal.ray_y);
	find_ray(&cal, data);
	dda_alg(data, &cal);
	// printf("%f \n", angle);
	return (find_distance(data, &cal, angle));
}

void	draw_3d_map(t_cube *data)
{
	int		a;
	double	i;

	i = -0.3;
	a = 0;
	// printf("ray len %f\n",data->p.r);

	while (i < 0.3)
	{
		data->p.ray = len_find(data, data->p.pa + i);
		// printf("ray len %f\n",data->p.ray);
		
		walls(data, a);
		i += 0.0006;
		a++;
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	check_direction(t_cube *vars, t_position *m)
{

	// if (vars->map->map_data[m->x][m->y] == 'S')
	// 	vars->p.pa = 0.5 * M_PI;
	// if (vars->map->map_data[m->x][m->y] == 'W')
	// 	vars->p.pa = 1.0 * M_PI;
	// if (vars->map->map_data[m->x][m->y] == 'N')
	// 	vars->p.pa = 1.5 * M_PI;
	// if (vars->map->map_data[m->x][m->y] == 'E')
	// 	vars->p.pa = 2.0 * M_PI;
	// vars->p.px = (m->x * r) + r / 2; 
	// vars->p.py = (m->y * r) + r / 2; 
	// vars->p.pdx = lround((cos(vars->p.pa)) * 5);
	// vars->p.pdy = lround((sin(vars->p.pa)) * 5);
}

int	init_draw(t_cube *cube)
{
	int	r;


	cube->map->ratio = 50;
	r = cube->map->ratio;
	cube->width = cube->map->col * cube->map->ratio;
	cube->height =  cube->map->row * cube->map->ratio;
	printf("x=%d, y=%d\n", cube->width, cube->height);
	// check_direction(cube, cube->map->start_pos);
	// printf("%d %d \n",cube->map->start_pos->x, cube->map->start_pos->y);
	cube->p.x =(double)cube->map->start_pos->x;
	cube->p.y = (double)cube->map->start_pos->y;
	printf("%f %f \n",cube->p.x, cube->p.y);

	cube->p.pa = 1.5 * M_PI; 
	cube->mlx = mlx_init(cube->width, cube->height, "CUB3D", false);
	if (!(cube->mlx))
		exit(EXIT_FAILURE);
	cube->img = mlx_new_image(cube->mlx, cube->width, cube->height);
	cube->p.x += 0.5;
	cube->p.y += 0.5;
	printf("new  %f %f \n",cube->p.x, cube->p.y);

	// draw_2D_map(cube, r, 0);
	draw_3d_map(cube);
	mlx_loop_hook(cube->mlx, &hook, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
	return (EXIT_SUCCESS);
}

int	arg_check(int argc, char **argv)
{
	size_t	filename_len;

	if (argc != 2)
		put_error(NULL, "Invalid number of arguments!\n");
	filename_len = ft_strlen(argv[1]);
	if (filename_len < 4)
		put_error(NULL, "Invalid file name!\n");
	if (ft_strcmp(&argv[1][filename_len - 4], ".cub") != 0)
		put_error(NULL, "Invalid map file extension!\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	arg_check(argc, argv);
	cube = (t_cube *)malloc(sizeof(t_cube));
	if (!cube)
		put_error(cube, "Failed to initialize the game!\n");
	if (init_cube(cube))
		put_error(cube, "Failed to initialize the game!\n");
	if (parse_file(cube, argv[1]))
		put_error(cube, "Failed to parse map file!\n");
	if (init_draw(cube))
		put_error(cube, "Failed to draw the game!\n");
	return (0);
}

	// printf("x=%d, y=%d\n", cube->map->start_pos->x, cube->map->start_pos->y);
