/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:11:03 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/22 20:17:59 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_player(t_cube *cube)
{
	cube->p.x = (double)cube->map->start_pos->x + 0.5;
	cube->p.y = (double)cube->map->start_pos->y + 0.5;
	cube->p.x_camera = (cos(cube->p.pa));
	cube->p.y_camera = (sin(cube->p.pa));
	cube->p.game_speed = 0.3;
	if (cube->map->start_pos->dir == 'N')
		cube->p.pa = 1.5 * M_PI;
	if (cube->map->start_pos->dir == 'W')
		cube->p.pa = 1.0 * M_PI;
	if (cube->map->start_pos->dir == 'S')
		cube->p.pa = 0.5 * M_PI;
	if (cube->map->start_pos->dir == 'E')
		cube->p.pa = 2.0 * M_PI;
}

void	init_minimap(t_cube *cube)
{
	int		map_size;

	cube->mini.player_size = 4;
	cube->mini.draw_minimap = 1;
	if (cube->map->col > cube->map->row)
		map_size = cube->map->col;
	else
		map_size = cube->map->row;
	map_size = (int)(300 / map_size);
	if (map_size < 10)
		map_size = 10;
	if (map_size == 10 && (cube->map->col > 100 || cube->map->row > 100))
		cube->mini.draw_minimap = 0;
	cube->mini.block_size[0] = map_size;
	cube->mini.block_size[1] = map_size;
}

int	init_draw(t_cube *cube)
{
	cube->width = 1000;
	cube->height = 1000;
	cube->mlx = mlx_init(cube->width, cube->height, "CUB3D", false);
	if (!(cube->mlx))
		exit(EXIT_FAILURE);
	cube->img = mlx_new_image(cube->mlx, cube->width, cube->height);
	if (!(cube->img))
		exit(EXIT_FAILURE);
	init_player(cube);
	init_minimap(cube);
	mlx_loop_hook(cube->mlx, &hook, cube);
	draw_3d_map(cube);
	mlx_loop(cube->mlx);
	mlx_delete_image(cube->mlx, cube->img);
	mlx_terminate(cube->mlx);
	clean_cube(cube);
	return (EXIT_SUCCESS);
}

int	arg_check(int argc, char **argv)
{
	size_t	filename_len;

	if (argc != 2)
		put_error(NULL, "Invalid number of arguments!\n");
	filename_len = ft_strlen(argv[1]);
	if (filename_len < 5)
		put_error(NULL, "Invalid file name!\n");
	if (argv[1][filename_len - 5] && argv[1][filename_len - 5] == '/')
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
