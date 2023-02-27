#ifndef CUBE3D_H
#define CUBE3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "../lib/get_next_line/get_next_line.h"
#include "../lib/libft/libft.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512

/*
The struct of everything
*/
typedef struct s_cube
{
	t_texture	textures;
	t_map		map;

	//to be continue...

} t_cube;

/*
The pattern/texture of the walls in four direction
*/
typedef struct s_texture
{
	t_img	n_tex;
	t_img	s_tex;
	t_img	w_tex;
	t_img	e_tex;
	t_colour floor;
	t_colour ceiling;
} t_texture;

/*
The colour of the floor and the ceiling
*/
typedef struct s_colour
{
	int colour;
	int r;
	int g;
	int b;
} t_colour;

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
	char	**data;
	int		row;
	int		col;

} t_map;

typedef struct s_img
{
	void	*mlx_img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
} t_img;

/****Parse****/
int parse_file(t_cube *cube, char *file);


#endif