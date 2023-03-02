#include <stdio.h>
#include "../lib/libft/libft.h"
#include <stdlib.h>

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
			// 		vars->player.y = 200;
			// 		vars->player.x =200 ;
				
			// 		vars->player.pa = 2 * M_PI;
			// 		vars->player.d_x = lround((cos(vars->player.pa)));
			// 		vars->player.d_y = lround((sin(vars->player.pa)));
			// 		printf("dx %f dy %f\n",vars->player.d_x, vars->player.d_y);
			// 		// printf("x %d y %d ,angel value = %f, y value = %f\n",vars->player.x, vars->player.y ,vars->player.d_x, vars->player.d_y);
				}
			y++;
		}
		x++;
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