/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_wall.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 15:22:30 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/15 18:14:03 by hwang         ########   odam.nl         */
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
Get img from path
*/
void	get_texture(t_cube *cube, mlx_texture_t *tex, char *path)
{
	int	len;
	int	fd;

	len = ft_strlen(path);
	if (ft_strcmp(&path[len - 4], ".png") != 0)
		put_error(cube, "Invalid texture file fomat!\n");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		put_error(cube, "Failed to open texture file!\n");
	tex = mlx_load_png(path);
	if (!tex)
		put_error(cube, "Failed to read texture file!\n");
}

/*
Currently just get the path to the texture!
*/
int	parse_wall(t_cube *cube, mlx_texture_t *tex, char *line, int i)
{
	char	*path;
	int		path_len;

	// if (tex != NULL)
	// 	put_error(cube, "Duplicate wall texture!\n");
	i += 2;
	i = skip_all_space(line, i);
	path_len = 0;
	while (line[i + path_len] && line[i + path_len] != '\n')
		path_len++;
	path = get_path(line, i, path_len);
	if (!path)
		put_error(cube, "Failed to get wall texture path!\n");
	printf("wall path is: %s\n", path);
	get_texture(cube, tex, path);
	(cube->textures->count)++;
	return (0);
}
