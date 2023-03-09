/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:03:43 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/08 16:42:45 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../lib/libft/libft.h"
#include <stdlib.h>
#include <math.h>

#include <memory.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_player
{
	int		px;			//player position
	int		py;
	double	pdx;		//player delta 
	double	pdy;
	double	pa; 	//player angle
	
	int		ray[60];
}			t_player;


typedef struct s_map
{
	int		ratio;
	int		line;
	int		len;
	char	**maps;

	int		mx;			//current map position
	int		my;
}			t_map;

typedef struct s_vars
{
	mlx_image_t*	map2D;
	mlx_image_t*	player;
	mlx_t*			mlx;
	t_player		p;
	t_map			map;
	int				width;
	int				height;
}			t_vars;
