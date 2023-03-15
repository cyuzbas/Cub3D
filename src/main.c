/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 13:04:11 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/15 13:57:48 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static mlx_image_t* img;

void hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		img->instances[0].x += 5;
}

// int32_t	main(void)
// {
// 	mlx_t* mlx;

// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 		return(EXIT_FAILURE);

// 	img = mlx_new_image(mlx, 128, 128);
// 	memset(img->pixels, 255, img->width * img->height * sizeof(int));
// 	mlx_image_to_window(mlx, img, 0, 0);

// 	mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);

// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

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
	return (0);
}
