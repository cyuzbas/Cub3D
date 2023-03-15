#ifndef CUBE3D_H
#define CUBE3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <fcntl.h>
#include <errno.h>
#include "../lib/libft/libft.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512

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
	t_texture	*textures;
	t_map		*map;

	//to be continue...

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

#endif