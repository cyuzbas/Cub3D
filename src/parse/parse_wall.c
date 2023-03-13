/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_wall.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 15:22:30 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/12 20:03:16 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*get_path(char *line, int i, int path_len)
{
	char	*path;
	int		j;

	j = 0;
	path = malloc(sizeof(char) * (path_len + 1));
	if (!path)
		return (0);
	while (line[i] && j < path_len)
	{
		path[j] = line[i];
		i++;
		j++;
	}
	path[j] = '\0';
	return (path);
}

/*
Currently just get the path to the texture!
*/
int	parse_wall(t_cube *cube, char *tex, char *line, int i)
{
	char	*path;
	int		path_len;

	if (tex != NULL)
		put_error(cube, "Duplicate wall texture!\n");
	i += 2;
	i = skip_all_space(line, i);
	path_len = 0;
	while (line[i + path_len] && line[i + path_len] != '\n')
		path_len++;
	path = get_path(line, i, path_len);
	if (!path)
		put_error(cube, "Failed to get wall texture path!\n");
	tex = path; //to be modified.
	printf("wall path is: %s\n", tex);
	(cube->textures->count)++;
	return (0);
}
