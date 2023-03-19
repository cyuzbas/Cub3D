/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 12:41:59 by cyuzbas       #+#    #+#                 */
/*   Updated: 2023/03/19 22:08:28 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_player(t_cube* vars);


void	put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= image->width || x < 0)
		return ;
	if (y >= image->height || y < 0)
		return ;
	mlx_put_pixel(image, x, y, color);
}

int	draw_rectangle(int pos[2], int dimensions[2], mlx_image_t *img, char map_element)
{
	const int	x = pos[0];
	const int	y = pos[1];
	int			w;
	int			h;

	w = 0;
	while (w < dimensions[0])
	{
		h = 0;
		while (h < dimensions[1])
		{
			if (map_element == '1')
				put_pixel(img, x + w , y - h, WHITE);
			else if (map_element == ' ')
				put_pixel(img, x + w, y - h, GREY);
			else if (map_element == 'P')
				put_pixel(img, x + w, y + h, RED);
			else
				put_pixel(img, x + w, y - h, BLACK);
			h++;
		}
		w++;
	}
	return (0);
}

// void	draw_line(mlx_image_t *data, t_point *p1, t_point *p2, int color)
// {
// 	double	slope;

// 	if ((int)p1->x == (int)p2->x && (int)p1->y == (int)p2->y)
// 		return ;
// 	else if ((int)p1->x == (int)p2->x)
// 		slope = 1;
// 	else
// 		slope = dabs((p1->y - p2->y) / (p1->x - p2->x));
// 	if (slope < 1)
// 		put_line_steap(data, p1, p2, color);
// 	else
// 		put_line_gentle(data, p1, p2, color);
// }

// static int	draw_direction(t_cube *config, mlx_image_t *img)
// {
// 	t_position	p1;
// 	t_position	p2;

// 	p1.x = config->p.x * config->mini.block_size[0];
// 	p1.y = config->p.y * config->mini.block_size[1];
// 	p2.x = (config->p.x + config->direction[0]) * config->mini.block_size[0];
// 	p2.y = (config->p.y + config->direction[1]) * config->mini.block_size[1];
// 	p1.y = img->height - p1.y;
// 	p2.y = img->height - p2.y;
// 	draw_line(img, &p1, &p2, WHITE);
// 	return (0);
// }


void	draw_minimap(t_cube *cube, mlx_image_t *img)
{
	int			x;
	int			y;
	int			pos[2];

	y = 0;
	while (y < cube->map->row)
	{
		x = 0;
		while (x < cube->map->col)
		{
			
			pos[0] = x * (int)(cube->mini.block_size[0]);
			pos[1] = img->height - ((cube->mini.block_size[1])*cube->map->row) + (y * (int)(cube->mini.block_size[1]));
			draw_rectangle(pos, cube->mini.block_size, \
			img, cube->map->map_data[y][x]);
			x++;
		}
		y++;
	}
	draw_player(cube);
	// draw_direction(cube, img);
}

// void draw_direction(t_cube *vars, double angle, int size)
// {
// 	t_map *map = vars->map;
// 	double x1;
//     double y1;
	
//     for(int i = 0; i < 20; i++)
//     {
//         x1 = (i * cos((angle))) + vars->p.y + 1;
//         y1 = (i * sin((angle))) + vars->p.x + 1;	
// 	int xof= x1 * 15;
// 	int yof= vars->img->height - ((vars->mini.block_size[1])*vars->map->row) + (y1 * (int)(vars->mini.block_size[1])) - 20;
//         // printf("player x %d y %d\n",(int)x1,(int)y1);
// 		// exit(0);
// 		if (x1 < map->col * map->ratio && x1 > 0  && 
// 			y1 < map->row * map->ratio && y1 > 0)
//             mlx_put_pixel(vars->img, x1+xof, y1+yof, 0XFF00FFFF);
//     }
// }

// void	check_direction(t_cube *vars, t_position *m, int r,int flag)
// {
// 	draw_block(vars->img, m, r, 0X000000FF);
// 	if (flag == 0)
// 	{
// 		if (vars->map->map_data[m->x][m->y] == 'S')
// 			vars->p.pa = 0.5 * M_PI;
// 		if (vars->map->map_data[m->x][m->y] == 'W')
// 			vars->p.pa = 1.0 * M_PI;
// 		if (vars->map->map_data[m->x][m->y] == 'N')
// 			vars->p.pa = 1.5 * M_PI;
// 		if (vars->map->map_data[m->x][m->y] == 'E')
// 			vars->p.pa = 2.0 * M_PI;
// 		vars->p.px = (m->x * r) + r / 2; 
// 		vars->p.py = (m->y * r) + r / 2; 
// 		vars->p.pdx = lround((cos(vars->p.pa)) * 5);
// 		vars->p.pdy = lround((sin(vars->p.pa)) * 5);
// 	}
// }

void draw_player(t_cube* vars)
{
	int size[2];
	int	pos[2];
	int	off[2];

	size[0] = vars->mini.player_size;
	size[1] = vars->mini.player_size;
	int x = (int)vars->p.x;
	int y = (int)vars->p.y;
	off[0]= (int)(x * (int)vars->mini.block_size[0]);
	off[1]= vars->img->height - ((vars->mini.block_size[1])*vars->map->row) + (y * (int)(vars->mini.block_size[1])) - (int)(vars->mini.player_size);

	while (vars->p.x > x - size[0])
	{
		y = vars->p.y;
		while (y - size[1] < vars->p.y)
		{
			draw_rectangle(off, size, vars->img, 'P');
			y++;
		}
		x++;
	}
	// draw_direction(vars, vars->p.pa, 10);
}
