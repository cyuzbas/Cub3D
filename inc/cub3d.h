/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 19:07:36 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/20 15:08:13 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <memory.h>
# include <fcntl.h>
# include <errno.h>

# define GREY			0X808080FF
# define RED			0XFF0000FF
# define WHITE			0XFFFFFFFF
# define BLACK			0X000000FF

typedef enum e_side
{
	EAST = 0,
	SOUTH = 1,
	WEST = 2,
	NORTH = 3
}	t_side;

typedef enum s_objects
{
	EMPTY = 0,
	FLOOR = 1,
	WALL = 2
}	t_objects;

typedef struct s_draw_info
{
	int				top;
	int				bottom;
	unsigned int	color;
	double			step;
	mlx_texture_t	*tex;
	double			text_start;
}					t_draw_info;

/*
To calculate ray length according to DDA algorithm
*/
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
	double		x;
	double		y;
	double		pa;
	double		game_speed;
	double		x_camera;
	double		y_camera;
	double		ray;
	t_side		side_enum;
	int			side;
	double		wall_x;

}			t_player;

/*
The colour of the floor and the ceiling
*/
typedef struct s_colour
{
	unsigned int	rgb;
	int				r;
	int				g;
	int				b;
	int				a;
}			t_colour;

/*
The pattern/texture of the walls in four direction
*/
typedef struct s_texture
{
	int				count;
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;
	t_colour		*floor;
	t_colour		*ceiling;
}				t_texture;

/*
The start position and direction
*/
typedef struct s_position
{
	int		x;
	int		y;
	char	dir;
}				t_position;

/*
The map struct
*/
typedef struct s_map
{
	int			ratio;
	char		*raw_map;
	char		**map_data;
	t_position	*start_pos;
	int			row;
	int			col;
}			t_map;

typedef struct s_minimap
{
	int	player_size;
	int	block_size[2];
	int	draw_minimap;
}				t_minimap;

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
	t_minimap		mini;
	int				width;
	int				height;
	float			direction[2];
}				t_cube;

/****Parse****/
int		parse_file(t_cube *cube, char *file);
int		skip_all_space(char *line, int i);
int		parse_wall(t_cube *cube, char *line, int i, char *wall_dir);
int		parse_colour(t_cube *cube, t_colour *colour, char *line, int i);

int		get_raw_map( t_cube *cube, char *line);
int		get_map_data(t_cube *cube);
int		check_map(t_cube *cube);

/****Parse****/
char	*get_next_line(int fd);
char	*ft_strjoin2(char *s1, char *s2);

/****Init****/
int		init_cube(t_cube *cube);

/****Clean****/
void	free_double_array(char **array);
void	put_error(t_cube *cube, char *str);

/****Drawing****/
void	draw_3d_map(t_cube *data);
void	walls(t_cube *data, int i);
void	hook(void *param);
void	draw_minimap(t_cube *cube, mlx_image_t *img);

#endif
