/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 18:23:45 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/17 16:46:42 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_rgb_format(char *line, int i)
{
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] && line[i] == ',')
		i++;
	else
		return (-1);
	if (ft_isdigit(line[i]))
	{
		while (line[i] && ft_isdigit(line[i]))
			i++;
		if (line[i] && line[i] == ',')
			i++;
		else
			return (-1);
	}
	if (ft_isdigit(line[i]))
	{
		while (line[i] && ft_isdigit(line[i]))
			i++;
	}
	if (line[i] == '\n')
		return (0);
	else
		return (-1);
}

int	parse_colour(t_cube *cube, t_colour *colour, char *line, int i)
{
	char	**rgb;

	i++;
	i = skip_all_space(line, i);
	if (check_rgb_format(line, i) == -1)
		put_error(cube, "Wrong rgb colour format for floor/ceiling!\n");
	rgb = ft_split(&line[i], ',');
	if (ft_strlen(rgb[0]) > 3 || ft_strlen(rgb[1]) > 3 || ft_strlen(rgb[2]) > 4)
		put_error(cube, "Wrong rgb colour format for floor/ceiling!\n");
	colour->r = ft_atoi(rgb[0]);
	colour->g = ft_atoi(rgb[1]);
	colour->b = ft_atoi(rgb[2]);
	printf("r=%d, g=%d, b=%d, a=%d\n", colour->r, colour->g, colour->b, colour->a);
	if (colour->r > 255 || colour->g > 255 || colour->b > 255)
		put_error(cube, "Wrong rgb colour value for floor/ceiling!\n");
	colour->rgb = (colour->r << 24 | colour->g << 16 | colour->b << 8 | colour->a);
	printf("rgb=%d\n", colour->rgb);
	
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	cube->textures->count++;
	return (0);
}
