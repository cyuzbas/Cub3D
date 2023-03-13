/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 16:56:18 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/13 12:40:48 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// int check_closed(t_cube *cube)
// {
// 	char **map = cube->map;
	
// 	if (x >= 0 && y >= 0 && x < row && y < col)
// 	{
// 		if (map[x][y] != '0')
// 			return ;
// 		if (check_neighbour(map[x][y]) == 0)
// 			return ;
		
// 	}
// }

void find_start(t_map *map)
{
	int i;
	int j;
	while(i < map->row)
	{
		while(j < map->col)
		{
			if (map->map_data[i][j] == map->start_pos->dir)
			{
				map->start_pos->x = j;
				map->start_pos->y = i;
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
	find_start(cube->map);
	// check_closed(cube->map);
}