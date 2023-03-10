/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/26 11:45:10 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/13 12:41:48 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	skip_all_space(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\v' || line[i] == '\f' || line[i] == '\r')
		i++;
	return (i);
}

int	get_map_info(t_cube *cube, char *line)
{
	int	i;

	i = 0;
	i = skip_all_space(line, i);
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (parse_wall(cube, cube->textures->no_tex, line, i));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (parse_wall(cube, cube->textures->so_tex, line, i));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (parse_wall(cube, cube->textures->we_tex, line, i));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (parse_wall(cube, cube->textures->ea_tex, line, i));
	else if (line[i] == 'F')
		parse_colour(cube, cube->textures->floor, line, i);
	else if (line[i] == 'C')
		return (parse_colour(cube, cube->textures->ceiling, line, i));
	else if (line[i] == '0' || line[i] == '1')
		return (get_raw_map(cube, line));
	else if (line[i] == '\n' && cube->map->raw_map != NULL)
	{
		put_error(cube, "Empty line in map!\n");
		return (-1);
	}
	else
	{
		if (line[i] == '\n')
			return (0);
		else
			return (-1);
	}
	return 0;
}

/*
Get all info from the file, textures and map
*/
int	parse_file(t_cube *cube, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		put_error(cube, "Failed to open map file!\n");
	while (1)
	{
		line = get_next_line(fd);
		if (line == (char *)-1)
			put_error(cube, "Failed to read map file!\n");
		if (line == 0)
			break ;
		if (get_map_info(cube, line) == -1)
			put_error(cube, "Invalid line on map file!\n");
		free(line);
	}
	close(fd);
	if (cube->textures->count != 6)
		put_error(cube, "Map file info is not complete!\n");
	if (cube->map->raw_map == NULL)
		put_error(cube, "Map not found in map file!\n");
	if (cube->map->start_pos->dir == 0)
		put_error(cube, "Start point not found in map!\n");
	get_map_data(cube);
	// if (!check_map(cube))
		// return (1);
	return (0);
}
