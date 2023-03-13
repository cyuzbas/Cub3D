/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 16:56:18 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/13 15:57:41 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int check_neighbour(char **map, int i, int j, char dir)
{
	if (map[i][j] == '0' || map[i][j] == dir)
	{
		if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || \
		map[i][j - 1] == ' ' || map[i][j + 1] == ' ' ||\
		map[i - 1][j - 1] == ' ' || map[i - 1][j + 1] == ' ' ||\
		map[i + 1][j - 1] == ' ' || map[i + 1][j + 1] == ' ')
			return (1);
	}
	return (0);
}

int check_closed(t_cube *cube, char **map, int x, int y)
{
	int col;
	int row;

	col = cube->map->col;
	row = cube->map->row;

	int i = 0;
	while (i < row)
	{
		int j = 0;
		while(j < col)
		{
			if (i == 0 || i == row - 1 || j == 0 || j == col - 1)
			{
				if (map[i][j] == '0')
					return (1);
			}
			else
			{
				if (check_neighbour(map, i, j, cube->map->start_pos->dir))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void find_start(t_map *map)
{
	int i;
	int j;

	i = 0;
	printf("col is: %d\n", map->col);
	printf("row is: %d\n", map->row);
	printf("start pos is: %c\n", map->start_pos->dir);
	while(i < map->row)
	{
		j = 0;
		while(j < map->col)
		{
			if (map->map_data[i][j] == map->start_pos->dir)
			{
				map->start_pos->x = j;
				map->start_pos->y = i;
				// printf("start x is: %d\n", map->start_pos->x);
				// printf("start y is: %d\n", map->start_pos->y);
				return ;
			}
			j++;
		}
		i++;
	}
	return ;
}

int check_map(t_cube *cube)
{
	find_start(cube->map); //get the x and y of the starting position!
	if (check_closed(cube, cube->map->map_data, cube->map->start_pos->x, cube->map->start_pos->y))
		put_error(cube, "Unclosed map\n");
	return (0);
}