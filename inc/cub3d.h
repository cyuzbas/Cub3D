/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:03:43 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/15 15:44:07 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <errno.h>

typedef struct s_player
{
	double	px;			//player position
	double	py;
	double	pa; 		//player angle
	double	pdx;		//player delta 
	double	pdy;
	int		ray[60];	//ray between -30/30 degrees
}			t_player;


// typedef struct s_map
// {
// 	int		ratio;
// 	int		line;
// 	int		len;
// 	char	**maps;

// 	int		mx;			//current map position
// 	int		my;
// }			t_map;

// typedef struct s_vars
// {
// 	mlx_image_t*	img;
// 	mlx_t*			mlx;
// 	t_player		p;
// 	t_map			map;
// 	int				width;
// 	int				height;
// }			t_vars;




/*
The colour of the floor and the ceiling
*/
typedef struct s_colour
{
	unsigned int rgb;
	int r;
	int g;
	int b;
} t_colour;

/*
The pattern/texture of the walls in four direction
*/
typedef struct s_texture
{
	int		count;
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;
	t_colour *floor;
	t_colour *ceiling;
} t_texture;

/*
The start position and direction
DO I NEED TO SAVE THE START POSITION??
*/
typedef struct s_position
{
	int	x;
	int y;
	char dir;
} t_position;

/*
The map struct
*/
typedef struct s_map
{
	int		ratio;
	char	*raw_map;
	char	**map_data;
	t_position	*start_pos;
	int		row;
	int		col;

} t_map;


/*
The struct of everything
*/
typedef struct s_cube
{
	t_texture		*textures;
	t_map			*map;

	mlx_image_t		*img;
	mlx_t			*mlx;
	t_player		p;
	// t_map			map;
	int				width;
	int				height;

} t_cube;

/****Parse****/
int	parse_file(t_cube *cube, char *file);
int	skip_all_space(char *line, int i);
int parse_wall(t_cube *cube, mlx_texture_t *tex, char *line, int i);
int parse_colour(t_cube *cube, t_colour *colour, char *line, int i);

int		get_raw_map( t_cube *cube, char *line);
int		get_map_data(t_cube *cube);
int		check_map(t_cube *cube);

/****Parse****/
char	*get_next_line(int fd);
char	*ft_strjoin2(char *s1, char *s2);

/****Init****/
int	init_cube(t_cube *cube);

/****Clean****/
void	free_double_array(char **array);
void	put_error(t_cube *cube, char *str);


/****Drawing****/
void draw_2D_map(t_cube *vars, int r, int flag);
void draw_player(t_cube	*vars);
void draw_direction(t_cube *vars, double angle, int size);


#endif
