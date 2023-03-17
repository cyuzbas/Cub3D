/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:11:03 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/17 19:05:39 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	check_direction(t_cube *vars, t_position *m)
// {

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
// }

int	init_draw(t_cube *cube)
{
	int	r;

	cube->map->ratio = 50;
	r = cube->map->ratio;
	cube->width = cube->map->col * cube->map->ratio;
	cube->height = cube->map->row * cube->map->ratio;
	printf("x=%d, y=%d\n", cube->width, cube->height);
	cube->p.x = (double)cube->map->start_pos->x;
	cube->p.y = (double)cube->map->start_pos->y;
	cube->p.game_speed = 0.2;
	cube->p.pa = 1.5 * M_PI;
	cube->mlx = mlx_init(cube->width, cube->height, "CUB3D", false);
	if (!(cube->mlx))
		exit(EXIT_FAILURE);
	cube->img = mlx_new_image(cube->mlx, cube->width, cube->height);
	cube->p.x += 0.5;
	cube->p.y += 0.5;
	cube->p.x_camera = lround((cos(cube->p.pa)));
	cube->p.y_camera = lround((sin(cube->p.pa)));
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
