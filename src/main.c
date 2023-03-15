/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
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
#include "cub3d.h"

void hook(void* param)
{
	t_cube* vars = param;
	mlx_t* mlx = vars->mlx;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

	// ft_memset(vars->map2D->pixels,  255 , vars->map2D->width * vars->map2D->height * sizeof(int));
	// ft_memset(vars->player->pixels,  0 , vars->player->width * vars->player->height * sizeof(int));
	ft_memset(vars->img->pixels,  0, vars->img->width * vars->img->height * sizeof(int));
	// free(vars->img);
	// vars->img = mlx_new_image(vars->mlx, vars->width, vars->height);
	
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		// printf("\n LEFT\n--------------------\n");
		// printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		vars->p.pa -= 0.05 *  M_PI;
		if (vars->p.pa < 0)
			vars->p.pa += 2 * M_PI;
		vars->p.pdx = cos(vars->p.pa) * 5;
		vars->p.pdy = sin(vars->p.pa) * 5;
		// printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		// printf("\n RIGHT\n--------------------\n");
		// printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		vars->p.pa += 0.05 *  M_PI;
		if (vars->p.pa > 2 * M_PI)
			vars->p.pa -= 2 * M_PI;
		vars->p.pdx = cos(vars->p.pa) * 5;
		vars->p.pdy = sin(vars->p.pa) * 5;
		// printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		// printf("\n UP\n--------------------\n");
		
		// printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
		vars->p.py += vars->p.pdx;
		vars->p.px += vars->p.pdy;
		// printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		// printf("\n DOWN\n--------------------\n");
		
		// printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
		vars->p.py -= vars->p.pdx;
		vars->p.px -= vars->p.pdy;
		// printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
		
	}
	draw_2D_map(vars, vars->map->ratio, 1);
}

int find_ray_len(int x, int y)
{
    if (x == 0)
        return (abs(y));
    else if (y == 0)
        return (abs(x));
    int result = (x * x) + (y * y);
    return (sqrt(result));
}

int check_walls(double player_x, double player_y, t_cube *vars)
{
    double wall_x;
    double wall_y;

    wall_x = player_x / 50;
    wall_y = player_y /50;
    // printf("walls float %f int %d float %f int %d [%c]\n",wall_x, (int) wall_x,wall_y, (int)wall_y ,vars->map_info.maps[(int)wall_y][(int)wall_x]);
    if (vars->map->map_data[(int)wall_y][(int)wall_x] == '1')
        return (0);
    return (1);    
}

int draw_ray(t_cube *data, double angle, long color)
{
    double x1;
    double y1;
	int  i = 0;
	double len;
	double oldx;
	double oldy;
	// oldy = (int)(i * sin(angle)) + data->p.px;
    // oldx = (int)(i * cos(angle)) + data->p.px;
	// printf("angel %f\n",angle);
    while(1)
    {
        x1 = (i * cos(angle)) + data->p.py + 1;
        y1 = (i * sin(angle)) + data->p.px + 1;
		// printf("x %d y %d ,angel value = %f, y value = %f\n",data->player.x, data->player.y ,data->player.d_x, data->player.d_y);	
        // printf("x1 %d y1 %d\n",x1,y1);
		if (x1 < data->map->col * 50 && x1 > 0  && y1 < data->map->row * 50 && y1 > 0)
		{
			if (check_walls(x1, y1, data))
			{
            	mlx_put_pixel(data->img, x1 , y1, color);
				// printf("ray x %d y %d\n",x1,y1);
			}
			else
				break;
		}
		else
		{
			break;
		}
		i++;
    }

	// printf("new x %d - old x %d = %d. and new y %d - old y %d = %d\n",x1,oldx, x1-oldx, y1,oldy, y1-oldy);
	len = find_ray_len(x1-oldx, y1-oldy);
	return (len);
}

void draw_direction(t_cube *vars, double angle, int size)
{
	t_map *map = vars->map;
	double x1;
    double y1;
    for(int i = 0; i < size; i++)
    {
        x1 = (i * cos((angle))) + vars->p.py + 1;
        y1 = (i * sin((angle))) + vars->p.px + 1;	
        if (x1 < map->col * map->ratio && x1 > 0  && y1 < map->row * map->ratio && y1 > 0)
            mlx_put_pixel(vars->img, x1, y1, 0XFF00FFFF);
    }
}

void draw_player(t_cube* vars)
{
	int size = 3;

	int x = (int)vars->p.px;
	int y = (int)vars->p.py;
	// printf("player x %d y %d\n",(int)vars->p.px,(int)vars->p.py);
	while (vars->p.px > x - size)
	{
		y = vars->p.py;
		while (y - size < vars->p.py)
		{
			mlx_put_pixel(vars->img, y, x, 0XFFFF00FF);
			y++;
		}
		x++;
	}

	int a = 0;
	for (double i = -0.3; i < 0.3; i+=0.01)
	{
	
		vars->p.ray[a] = draw_ray(vars, vars->p.pa + i, 0XFF0000FF);
		a++;
	}
	draw_direction(vars, vars->p.pa, 10);
}

void draw_block(mlx_image_t* map2D, t_position *m, int r, int color)
{
	int y = m->x * r;
	int x = m->y * r;
	

	while (x < (m->y * r) + (r - 1))
	{
		y = m->x * r;
		while (y < (m->x * r) + (r - 1) )
		{
			mlx_put_pixel(map2D, x, y, color);
			y++;
		}
		x++;
	}
}

void draw_2D_map(t_cube *vars, int r, int flag)
{
	t_position *m;

	m = vars->map->start_pos;
	m->x = 0;
	while (vars->map->map_data[m->x])
	{
		m->y = 0;
		while (vars->map->map_data[m->x][m->y])
		{
			if (vars->map->map_data[m->x][m->y] == '0')
				draw_block(vars->img, m, r, 0X000000FF);
			else if (vars->map->map_data[m->x][m->y] == '1')
				draw_block(vars->img, m, r, 0XFFFFFFFF);
			else if (vars->map->map_data[m->x][m->y] == 'N' ||
					vars->map->map_data[m->x][m->y] == 'E' ||
					vars->map->map_data[m->x][m->y] == 'S' ||
					vars->map->map_data[m->x][m->y] == 'W')
			{
				draw_block(vars->img, m, r, 0X000000FF);
				if (flag == 0)
				{
					vars->p.px = (m->x * r) + r / 2; 
					vars->p.py = (m->y * r) + r / 2; 
					vars->p.pa = 2 * M_PI;
					vars->p.pdx = lround((cos(vars->p.pa)));
					vars->p.pdy = lround((sin(vars->p.pa)));
				}
			}
			m->y++;
		}
		m->x++;
	}
	// printf("player x %d y %d, flag = %d\n",(int)vars->p.px,(int)vars->p.py, flag);
	draw_player(vars);
	mlx_image_to_window(vars->mlx, vars->img, 0, 0);
}

int	init_draw(t_cube *cube)
{
	int	r;

	cube->map->ratio = 50;
	r = cube->map->ratio;
	cube->width = cube->map->col * cube->map->ratio;
	cube->height =  cube->map->row * cube->map->ratio;
	cube->mlx = mlx_init(cube->width, cube->height, "CUB3D", false);
	if (!(cube->mlx))
		exit(EXIT_FAILURE);
	cube->img = mlx_new_image(cube->mlx, cube->width, cube->height);
	draw_2D_map(cube, r, 0);
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

