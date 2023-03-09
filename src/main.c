/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:11:03 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/09 14:47:18 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../lib/libft/libft.h"
#include <stdlib.h>
#include <math.h>

#include <memory.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "cub3d.h"

void draw_2D_map(t_vars *vars);
void draw_player(t_vars* vars, t_map map);
void draw_direction(t_vars *vars, double angle, int x, int y);

t_map	fill_map(t_map map)
{
	map.ratio = 64;
	map.len = 15;
	map.line = 8;
	map.maps = malloc(sizeof(char**) * map.line + 1);
	map.maps[0] = malloc(sizeof(char *) * map.len + 1);
	map.maps[1] = malloc(sizeof(char *) * map.len + 1);
	map.maps[2] = malloc(sizeof(char *) * map.len + 1);
	map.maps[3] = malloc(sizeof(char *) * map.len + 1);
	map.maps[4] = malloc(sizeof(char *) * map.len + 1);
	map.maps[5] = malloc(sizeof(char *) * map.len + 1);
	map.maps[6] = malloc(sizeof(char *) * map.len + 1);
	map.maps[7] = malloc(sizeof(char *) * map.len + 1);
	map.maps[8] = malloc(sizeof(char *) * map.len + 1);
    map.maps[0] = "111111111111111";
	map.maps[1] = "101001000001001";
	map.maps[2] = "11010P010000101";
    map.maps[3] = "101001000000001";
    map.maps[4] = "101000000001001";
    map.maps[5] = "101000001001001";
    map.maps[6] = "101001000000001";
	map.maps[7] = "111111111111111";
	map.maps[8] = NULL;
	return (map);
}


void hook(void* param)
{
	t_vars* vars = param;
	mlx_t* mlx = vars->mlx;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		// printf("\nx=%d, y=%d\n", vars->player->instances[0].x, 
		// vars->player->instances[0].y);
		vars->player->instances[0].y -= 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		vars->player->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		vars->player->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		vars->player->instances[0].x += 5;
		
	// ft_memset(vars->map2D->pixels,  255 , vars->map2D->width * vars->map2D->height * sizeof(int));
	ft_memset(vars->player->pixels,  0 , vars->player->width * vars->player->height * sizeof(int));
	
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		// printf("\npa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		vars->p.pa -= 0.05 *  M_PI;
		if (vars->p.pa < 0)
			vars->p.pa += 2 * M_PI;
		vars->p.pdx = cos(vars->p.pa * 5);
		vars->p.pdy = sin(vars->p.pa * 5);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		vars->p.pa += 0.05 *  M_PI;
		if (vars->p.pa > 2 * M_PI)
			vars->p.pa -= 2 * M_PI;
		vars->p.pdx = cos(vars->p.pa * 5.0);
		vars->p.pdy = sin(vars->p.pa * 5.0);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		vars->player->instances[0].x += vars->p.pdx;
		vars->player->instances[0].y += vars->p.pdy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		vars->player->instances[0].x -= vars->p.pdx;
		vars->player->instances[0].y -= vars->p.pdy;
	}
	// draw_2D_map(vars);
	draw_player(vars, vars->map);
}


void draw_direction(t_vars *vars, double angle, int x, int y)
{
	t_map map = vars->map;
	double x1;
    double y1;

	// vars->p.pa = 1.5 * M_PI;
	// vars->p.pdx = lround((cos(vars->p.pa)));
	// vars->p.pdy = lround((sin(vars->p.pa)));
    for(int i = 0; i < 10; i++)
    {
        x1 = (i * cos((angle))) + x;
        y1 = (i * sin((angle))) + y;
		// printf("x %d X1 %f y %d  y1 %f i %d cos %d sin %d\n",x,x1,y,y1,i, (int)cos(2 * M_PI) , (int)sin(2 * M_PI));
		// printf("x %d y %d ,angel value = %f, y value = %f\n",data->player.x, data->player.y ,data->player.d_x, data->player.d_y);	
        if (x1 < map.len * map.ratio && x1 > 0  && y1 < map.line * map.ratio && y1 > 0)
            mlx_put_pixel(vars->player, x1, y1, 0XFF00FFFF);
    }
}

void draw_player(t_vars* vars, t_map map)
{
	int size = 6;
	int x;
	int y = (vars->p.py*map.ratio)+(map.ratio-size)/2;

	while (y < (vars->p.py*map.ratio)+(map.ratio-size)/2 + size)
	{
		x = (vars->p.px*map.ratio)+(map.ratio-size)/2;
		while (x < (vars->p.px*map.ratio)+(map.ratio-size)/2 + size)
		{
			mlx_put_pixel(vars->player, y, x, 0XFFFF00FF);
			x++;
		}
		y++;
	}
	draw_direction(vars, vars->p.pa, y-size/2, x-size/2);
	// mlx_image_to_window(vars->mlx, vars->player, 0, 0);

}

void draw_block(mlx_image_t* map2D, t_map map, int color)
{
	int x = map.mx * map.ratio;
	int y = map.my * map.ratio;
	

	while (y < (map.my * map.ratio) + (map.ratio - 1))
	{
		x = map.mx * map.ratio;
		while (x < (map.mx * map.ratio) + (map.ratio - 1) )
		{
			mlx_put_pixel(map2D, y, x, color);
			x++;
		}
		y++;
	}
}

void draw_2D_map(t_vars *vars)
{
	vars->map.mx = 0;
	while (vars->map.maps[vars->map.mx])
	{
		vars->map.my = 0;
		while (vars->map.maps[vars->map.mx][vars->map.my])
		{
			if (vars->map.maps[vars->map.mx][vars->map.my] == '0')
				draw_block(vars->map2D, vars->map, 0X00000055);
			else if (vars->map.maps[vars->map.mx][vars->map.my] == '1')
				draw_block(vars->map2D, vars->map, 0XFFFFFF99);
			else if (vars->map.maps[vars->map.mx][vars->map.my] == 'P' )
			{
				draw_block(vars->map2D, vars->map, 0X00000055);
				vars->p.px = vars->map.mx;
				vars->p.py = vars->map.my;
				vars->p.pa = 0.5 * M_PI;
				vars->p.pdx = lround((cos(vars->p.pa)));
				vars->p.pdy = lround((sin(vars->p.pa)));
			}
			vars->map.my++;
		}
		vars->map.mx++;
	}
	mlx_image_to_window(vars->mlx, vars->map2D, 0, 0);
	draw_player(vars, vars->map);
	mlx_image_to_window(vars->mlx, vars->player, 0, 0);
}

int	main(void)
{
	t_vars	vars;
	
	vars.map = fill_map(vars.map);
	vars.width = vars.map.len * vars.map.ratio;
	vars.height =  vars.map.line * vars.map.ratio;
	
	if (!(vars.mlx = mlx_init(vars.width, vars.height, "CUB3D", false)))
		exit(EXIT_FAILURE);
	
	vars.player = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.map2D = mlx_new_image(vars.mlx, vars.width, vars.height);

	draw_2D_map(&vars);
	
	mlx_loop_hook(vars.mlx, &hook, &vars);
	mlx_loop(vars.mlx);
	
	mlx_terminate(vars.mlx);
	
	return (EXIT_SUCCESS);
}