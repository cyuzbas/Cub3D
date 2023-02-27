/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/26 11:45:10 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/27 18:13:36 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int get_map_info(line)
{
	
}

int check_closed(char **map)
{
	if (x >= 0 && y >= 0 && x < row && y < col)
	{
		if (map[x][y] != '0')
			return ;
		if (check_neighbour(map[x][y]) == 0)
			return ;
		
	}
	
}

int check_map(char **map)
{
	check_content();
	check_closed(map);
}

int parse_file(t_cube *cube, char *file)
{
	int fd;
	int read;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		put_error("Failed to open map file!\n");
	while (read)
	{
		line = get_next_line(fd);
		// if (!line && read(fd, 0, 0) == 0)
			put_error("Failed to read map file!\n");
		if (!get_map_info(line))
			put_error("Invalid line on map file!\n");
		free(line);
	}
	close(fd);
	if (!check_map(cube->map))
		return (1);
	return (0);	
}