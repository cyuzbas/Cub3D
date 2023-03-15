/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:03:43 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/15 15:35:38 by cyuzbas       ########   odam.nl         */
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

typedef enum e_side
{
	EAST = 0,
	SOUTH = 1,
	WEST = 2,
	NORTH =3
}	t_side;

typedef struct s_calculation
{
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		ray_x;
	double		ray_y;
	double		delta_x;
	double		delta_y;
	double		side_x;
	double		side_y;
	int			hit;
}				t_calculation;

/*
Player position, angle, delta, and amount
of ray will be drawn between -30/30 degrees
*/
typedef struct s_player
{
	double	x;
	double	y;
	double	pa;
	// double	pdx;
	// double	pdy;
	
	int			x_view_direction;
	int			y_view_direction;
	double		game_speed;
	double		x_camera;
	double		y_camera;
	double	ray;
	t_side		side_enum;
	double		hitpos;
	int			hit_x;
	int			hit_y;
	int			side;
	double		wall_x;

}			t_player;


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
	// t_img	no_tex;
	// t_img	so_tex;
	// t_img	we_tex;
	// t_img	ea_tex;
	char	*no_tex;
	char	*so_tex;
	char	*we_tex;
	char	*ea_tex;
	t_colour *floor;
	t_colour *ceiling;
} t_texture;

/*
The start position and direction
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
int parse_wall(t_cube *cube, char *tex, char *line, int i);
int parse_colour(t_cube *cube, t_colour *colour, char *line, int i);

int		get_raw_map( t_cube *cube, char *line);
int		get_map_data(t_cube *cube);
void	put_error(t_cube *cube, char *str);

/****Parse****/
char	*get_next_line(int fd);
char	*ft_strjoin2(char *s1, char *s2);

int	init_cube(t_cube *cube);


/****Drawing****/
// void draw_2D_map(t_cube *vars, int r, int flag);
// void draw_player(t_cube	*vars);
// void draw_direction(t_cube *vars, double angle, int size);
void	draw_3d_map(t_cube *data);
void	walls(t_cube *data, int i);
#endif
