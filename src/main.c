#include <stdio.h>
#include "../lib/libft/libft.h"
#include <stdlib.h>
#include <math.h>

#include <memory.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"

static mlx_image_t* bckrnd;
static mlx_image_t* player;

typedef struct s_map
{
	int		line;
	int		len;
	char	**maps;
}			t_map;

void hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		player->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->instances[0].x += 5;
		
}

void create_block(mlx_image_t* bckrnd, int wall_x, int wall_y, int color)
{
	int x = wall_x * 50;
	int y = wall_y * 50;
	

	while (x < (wall_x * 50) + 49)
	{
		y = wall_y * 50;
		while (y < (wall_y * 50) + 49 )
		{
			mlx_put_pixel(bckrnd, x, y, color);
			y++;
		}
		x++;
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

void walls(mlx_image_t* bckrnd, t_map map, mlx_t* mlx, mlx_image_t* player)
{
	int x = 0;
	int y = 0;

	while (map.maps[x])
	{
		y = 0;
		while (map.maps[x][y])
		{
			if (map.maps[x][y] == '0')
				create_block(bckrnd, y, x, 0X99999999);
			else if (map.maps[x][y] == '1')
			{
				create_block(bckrnd, y, x, 0X320130);
			}
			else if (map.maps[x][y] == 'P' )
			{
				create_block(bckrnd, y, x, 0X99999999);
				mlx_image_to_window(mlx, player, (y*50)+23, (x*50)+23);
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
			y++;
		}
		x++;
		// create_player(vars, (int) vars->player.x, (int) vars->player.y);
		// mlx_put_image_to_window(vars->mlx, vars->win,
		// vars->background.img_ptr, 0, 0);
	}
	
}

int	main(void)
{

	mlx_t* mlx;
	t_map map;

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


	if (!(mlx = mlx_init(map.len*50, map.line*50, "CUB3D", true)))
		return(EXIT_FAILURE);

	player = mlx_new_image(mlx, 4, 4);
	bckrnd = mlx_new_image(mlx, map.len*50, map.line*50);

	ft_memset(player->pixels,  255 , player->width * player->height * sizeof(int));
	walls(bckrnd, map, mlx, player);

	// mlx_image_to_window(mlx, player, 320 , 170);
	mlx_image_to_window(mlx, bckrnd, 0, 0);

	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}