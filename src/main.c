/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/07 16:35:45 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/08 13:22:48 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../lib/libft/libft.h"
#include <stdlib.h>
#include <math.h>

#include <memory.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"

static mlx_image_t* map2D;
static mlx_image_t* player;
#define PI 3.1415926535

typedef struct s_map
{
	int		ratio;
	int		line;
	int		len;
	char	**maps;

	int		px;			//player position
	int		py;
	float	pdx;		//player delta 
	float	pdy;
	float	pangle; 	//player angle

	int		x;			//current position
	int		y;
}			t_map;



void hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		player->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player->instances[0].x += 5;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		player->instances[0].angle -= 0.1;
		if (player->instances[0].angle < 0)
			player->instances[0].angle += 2 * PI;
		player->instances[0].dx = cos(player->instances[0].angle * 5);
		player->instances[0].dy = sin(player->instances[0].angle * 5);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		player->instances[0].angle += 0.1;
		if (player->instances[0].angle > 2 * PI)
			player->instances[0].angle -= 2 * PI;
		player->instances[0].dx = cos(player->instances[0].angle * 5);
		player->instances[0].dy = sin(player->instances[0].angle * 5);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		player->instances[0].x += player->instances[0].dx;
		player->instances[0].y += player->instances[0].dy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		player->instances[0].x -= player->instances[0].dx;
		player->instances[0].y -= player->instances[0].dy;
	}
}

// void draw_angle(t_vars *data, double angle, int line_lenght, long color)
// {
//     double x1;
//     double y1;

//     for(int i = 0; i < line_lenght; i += 1)
//     {
//         x1 = (i * cos(angle)) + data->player.x + 1;
//         y1 = (i * sin(angle)) + data->player.y + 1;
// 		// printf("x %d y %d ,angel value = %f, y value = %f\n",data->player.x, data->player.y ,data->player.d_x, data->player.d_y);	
//         if (x1 < data->map_info.len * 50 && x1 > 0  && y1 < data->map_info.line * 50 && y1 > 0)
//             my_mlx_pixel_put(&data->background, x1, y1, color);
//     }
//     // printf("x value = %d, y value = %d\n", x1, y1);
// }

// void create_player(t_vars *vars, int player_x, int player_y)
// {

// 	int x = player_x;
// 	int y = player_y;
// 	printf("player x %d y %d\n",player_x,player_y);
	
// 	while (player_x > x - 3)
// 	{
// 		y = player_y;
// 		while (y - 3 < player_y)
// 		{
// 			my_mlx_pixel_put(&vars->background, x, y, 0X000000);
// 			y++;
// 		}
// 		x++;
// 	}
    
// 	int a = 0;
// 	for (double i = -0.3; i < 0.3; i+=0.01)
// 	{
	
// 		vars->player.ray[a] = draw_ray(vars, vars->player.pa + i, 0XFF0000);
// 		a++;
// 	}
// 	// draw_ray(vars, vars->player.pa, 0XFF0000);
// 	draw_angle(vars, vars->player.pa , 8, 0X000000);


// }

// void draw_player1(mlx_t* mlx, mlx_image_t* player, t_map map)
// {
// 	int x;
// 	int y = 0;
// 	int size = 4;
// 	int a = 0;
// 	int b = 0;
// 	while (map.maps[a])
// 	{
// 		b = 0;
// 		while (map.maps[a][b])
// 		{
// 			if(map.maps[a][b] == 'P')
// 			{
// 				while (y < size)
// 				{
// 					x = 0;
// 					while (x < size)
// 					{
// 						mlx_put_pixel(player, y, x, 0XFFFF00FF);
// 						x++;
// 					}
// 					y++;
// 				}
// 				y = (b*map.ratio)+(map.ratio-size)/2;
// 				x = (a*map.ratio)+(map.ratio-size)/2;
// 				mlx_image_to_window(mlx, player, y, x);
// 				break;
// 			}
// 			b++;
// 		}
// 		a++;
// 	}
// }

void draw_direction(mlx_image_t* player, t_map map, int x, int y)
{
	double x1;
    double y1;

    for(int i = 0; i < 10; i++)
    {
        x1 = (i * cos(0.5 * M_PI)) + x;
        y1 = (i * sin(0.5 * M_PI)) + y;
		// printf("x %d X1 %f y %d  y1 %f i %d cos %d sin %d\n",x,x1,y,y1,i, (int)cos(2 * M_PI) , (int)sin(2 * M_PI));
		// printf("x %d y %d ,angel value = %f, y value = %f\n",data->player.x, data->player.y ,data->player.d_x, data->player.d_y);	
        if (x1 < map.len * map.ratio && x1 > 0  && y1 < map.line * map.ratio && y1 > 0)
            {mlx_put_pixel(player, x1, y1, 0XFF00FFFF);
			printf("inside\n");}
    }
}

void draw_player(mlx_t* mlx, mlx_image_t* player, t_map map)
{
	int x;
	int y = 0;
	int size = 5;

	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_put_pixel(player, y, x, 0XFFFF00FF);
			x++;
		}
		y++;
	}
	
	draw_direction(player, map, 2, 2);
	y = (map.y*map.ratio)+(map.ratio-size)/2;
	x = (map.x*map.ratio)+(map.ratio-size)/2;
	mlx_image_to_window(mlx, player, y, x);

}

void create_block(mlx_image_t* bckrnd, t_map map, int color)
{
	int x = map.x * map.ratio;
	int y = map.y * map.ratio;
	

	while (y < (map.y * map.ratio) + (map.ratio - 1))
	{
		x = map.x * map.ratio;
		while (x < (map.x * map.ratio) + (map.ratio - 1) )
		{
			mlx_put_pixel(bckrnd, y, x, color);
			x++;
		}
		y++;
	}
}

void draw_2D_map(mlx_image_t* bckrnd, t_map map, mlx_t* mlx, mlx_image_t* player)
{
	map.x = 0;
	while (map.maps[map.x])
	{
		map.y = 0;
		while (map.maps[map.x][map.y])
		{
			if (map.maps[map.x][map.y] == '0')
				create_block(bckrnd, map, 0X00000055);
			else if (map.maps[map.x][map.y] == '1')
			{
				create_block(bckrnd, map, 0XFFFFFF99);
			}
			else if (map.maps[map.x][map.y] == 'P' )
			{
				create_block(bckrnd, map, 0X00000055);
				draw_player(mlx, player, map);
				// mlx_image_to_window(mlx, player, (y*map.ratio)+(map.ratio-4)/2, (x*map.ratio)+(map.ratio-4)/2);
			// 	if (where == 0)
			// 	{				
					// vars->player.y = 200;
					// vars->player.x =200 ;
				
					// vars->player.pa = 2 * M_PI;
					// vars->player.d_x = lround((cos(vars->player.pa)));
					// vars->player.d_y = lround((sin(vars->player.pa)));
					// printf("dx %f dy %f\n",vars->player.d_x, vars->player.d_y);
			// 		// printf("x %d y %d ,angel value = %f, y value = %f\n",vars->player.x, vars->player.y ,vars->player.d_x, vars->player.d_y);
				}
			map.y++;
		}
		map.x++;
		// create_player(vars, (int) vars->player.x, (int) vars->player.y);
		// mlx_put_image_to_window(vars->mlx, vars->win,
		// vars->background.img_ptr, 0, 0);
	}
	
}

int	main(void)
{

	mlx_t* mlx;
	t_map map;

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


	if (!(mlx = mlx_init(map.len * map.ratio, map.line * map.ratio, "CUB3D", true)))
		return(EXIT_FAILURE);

	player = mlx_new_image(mlx, 15, 15);
	map2D = mlx_new_image(mlx, map.len * map.ratio, map.line * map.ratio);


	// mlx_image_to_window(mlx, player, 320 , 170);
	mlx_image_to_window(mlx, map2D, 0, 0);

	// draw_player1(mlx, player, map);
	draw_2D_map(map2D, map, mlx, player);
	// ft_memset(player->pixels,  255 , player->width * player->height * sizeof(int));


	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}