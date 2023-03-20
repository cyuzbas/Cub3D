/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 15:40:10 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/20 15:00:12 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	map_char_check(char *line, int i, t_cube *cube)
{
	if (line[i] == ' ' || line[i] == '0' || line[i] == '1')
		i++;
	else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || \
		line[i] == 'E')
	{
		if (cube->map->start_pos->dir != 0)
			put_error(cube, "Duplicate starting point!\n");
		else
		{
			cube->map->start_pos->dir = line[i];
			i++;
		}
	}
	else
		put_error(cube, "Invalid character on map!\n");
	return (i);
}

/*
valid:	"     10000000N000001"
valid:	"     10000000N000001  11"
invalid:	"     10000000N0 0001  11", will be checked in next step
*/
int	map_line_check(char *line, t_cube *cube)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i = map_char_check(line, i, cube);
	if (line[i] && line[i] != '\n')
		return (-1);
	while (line[i - 1] == ' ')
		i--;
	if (cube->map->col < i)
		cube->map->col = i;
	(cube->map->row)++;
	return (0);
}

int	get_raw_map( t_cube *cube, char *line)
{
	char	*temp;

	if (map_line_check(line, cube) == 0)
	{
		temp = ft_strjoin2(cube->map->raw_map, line);
		if (!temp)
			put_error(cube, "Failed to get map!\n");
		cube->map->raw_map = temp;
	}
	else
		put_error(cube, "Invalid element in map!\n");
	return (0);
}

int	copy_map(char **temp, char **map, int col)
{
	int		i;
	int		j;

		i = 0;
	while (temp[i])
	{
		map[i] = malloc(sizeof(char) * (col + 1));
		if (!map[i])
			return (1);
		j = 0;
		while (temp[i][j])
		{
			map[i][j] = temp[i][j];
			j++;
		}
		while (j < col)
		{
			map[i][j] = ' ';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = 0;
	return (0);
}

/*
To print the map for check before free:
	i = 0;
	while (i < cube->map->row)
	{
		printf("%s\n", cube->map->map_data[i]);
		i++;
	}
*/
int	get_map_data(t_cube *cube)
{
	char	**temp;
	char	**map;

	temp = ft_split(cube->map->raw_map, '\n');
	map = malloc(sizeof(char *) * (cube->map->row + 1));
	if (!map)
		return (1);
	if (copy_map(temp, map, cube->map->col))
		return (1);
	free_double_array(temp);
	cube->map->map_data = map;
	return (0);
}
