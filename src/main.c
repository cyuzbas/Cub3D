/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:11:03 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/09 18:22:24 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../lib/libft/libft.h"
#include <stdlib.h>
#include <math.h>

#include <memory.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "cub3d.h"

void draw_2D_map(t_vars *vars, int flag);
void draw_player(t_vars* vars, t_map map);
void draw_direction(t_vars *vars, double angle, int size);

t_map	fill_map(t_map map)
{
	map.ratio = 50;
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

		
	// ft_memset(vars->map2D->pixels,  255 , vars->map2D->width * vars->map2D->height * sizeof(int));
	// ft_memset(vars->player->pixels,  0 , vars->player->width * vars->player->height * sizeof(int));
	ft_memset(vars->img->pixels,  0, vars->img->width * vars->img->height * sizeof(int));
	// free(vars->img);
	// vars->img = mlx_new_image(vars->mlx, vars->width, vars->height);
	
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		printf("\n LEFT\n--------------------\n");
		vars->p.pa -= 0.05 *  M_PI;
		printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		if (vars->p.pa < 0)
			vars->p.pa += 2 * M_PI;
		vars->p.pdx = cos(vars->p.pa) * 5;
		vars->p.pdy = sin(vars->p.pa) * 5;
		printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		printf("\n RIGHT\n--------------------\n");
		printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		vars->p.pa += 0.05 *  M_PI;
		if (vars->p.pa > 2 * M_PI)
			vars->p.pa -= 2 * M_PI;
		vars->p.pdx = cos(vars->p.pa) * 5;
		vars->p.pdy = sin(vars->p.pa) * 5;
		printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.pdx, vars->p.pdy);
		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		printf("\n UP\n--------------------\n");
		
		printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
		vars->p.py += vars->p.pdx;
		vars->p.px += vars->p.pdy;
		printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		printf("\n DOWN\n--------------------\n");
		
		printf("before pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
		vars->p.py -= vars->p.pdx;
		vars->p.px -= vars->p.pdy;
		printf("after pa=%f, pdx=%f, pdy=%f\n", vars->p.pa, vars->p.px, vars->p.py);
		
	}
	draw_2D_map(vars,1);
}


void draw_direction(t_vars *vars, double angle, int size)
{
	t_map map = vars->map;
	double x1;
    double y1;

    for(int i = 0; i < size; i++)
    {
        x1 = (i * cos((angle))) + vars->p.py + 1;
        y1 = (i * sin((angle))) + vars->p.px + 1;	
        if (x1 < map.len * map.ratio && x1 > 0  && y1 < map.line * map.ratio && y1 > 0)
            mlx_put_pixel(vars->img, x1, y1, 0XFF00FFFF);
    }
}

void draw_player(t_vars* vars, t_map map)
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
	draw_direction(vars, vars->p.pa, 10);
}

void draw_block(mlx_image_t* map2D, t_map map, int color)
{
	int y = map.mx * map.ratio;
	int x = map.my * map.ratio;
	

	while (x < (map.my * map.ratio) + (map.ratio - 1))
	{
		y = map.mx * map.ratio;
		while (y < (map.mx * map.ratio) + (map.ratio - 1) )
		{
			mlx_put_pixel(map2D, x, y, color);
			y++;
		}
		x++;
	}
}

void draw_2D_map(t_vars *vars, int flag)
{
	t_map m;

	m = vars->map;
	m.mx = 0;
	while (m.maps[m.mx])
	{
		m.my = 0;
		while (m.maps[m.mx][m.my])
		{
			if (m.maps[m.mx][m.my] == '0')
				draw_block(vars->img, m, 0X000000FF);
			else if (m.maps[m.mx][m.my] == '1')
				draw_block(vars->img, m, 0XFFFFFFFF);
			else if (m.maps[m.mx][m.my] == 'P' )
			{
				draw_block(vars->img, m, 0X000000FF);
				if (flag == 0)
				{
					vars->p.px = (m.mx * m.ratio) + 25; //352
					vars->p.py = (m.my * m.ratio) + 25; //160
					vars->p.pa = 2 * M_PI;
					vars->p.pdx = lround((cos(vars->p.pa)));
					vars->p.pdy = lround((sin(vars->p.pa)));
				}
			}
			m.my++;
		}
		m.mx++;
	}
	draw_player(vars, m);
	mlx_image_to_window(vars->mlx, vars->img, 0, 0);
}

int	main(void)
{
	t_vars	vars;
	
	vars.map = fill_map(vars.map);
	vars.width = vars.map.len * vars.map.ratio;
	vars.height =  vars.map.line * vars.map.ratio;
	
	if (!(vars.mlx = mlx_init(vars.width, vars.height, "CUB3D", false)))
		exit(EXIT_FAILURE);
	
	vars.img = mlx_new_image(vars.mlx, vars.width, vars.height);

	draw_2D_map(&vars, 0);
	
	mlx_loop_hook(vars.mlx, &hook, &vars);
	mlx_loop(vars.mlx);
	
	mlx_terminate(vars.mlx);
	
	return (EXIT_SUCCESS);
}