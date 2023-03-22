/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 18:23:45 by hwang         #+#    #+#                 */
/*   Updated: 2023/03/22 19:59:40 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	skip_digit(char *line, int i)
{
	while (line[i] && ft_isdigit(line[i]))
		i++;
	return (i);
}

int	check_rgb_format(char *line, int i)
{
	if (ft_isdigit(line[i]))
	{
		i = skip_digit(line, i);
		if (line[i] && line[i] == ',')
			i++;
		else
			return (-1);
	}
	if (ft_isdigit(line[i]))
	{
		i = skip_digit(line, i);
		if (line[i] && line[i] == ',')
			i++;
		else
			return (-1);
	}
	if (ft_isdigit(line[i]))
		i = skip_digit(line, i);
	if (line[i] == '\n')
		return (0);
	else
		return (-1);
}

int	parse_colour(t_cube *cube, t_colour *color, char *line, int i)
{
	char	**rgb;

	i++;
	i = skip_all_space(line, i);
	if (check_rgb_format(line, i) == -1)
		put_error(cube, "Wrong rgb colour format for floor/ceiling!\n");
	rgb = ft_split(&line[i], ',');
	if (ft_strlen(rgb[0]) > 3 || ft_strlen(rgb[1]) > 3 || ft_strlen(rgb[2]) > 4)
		put_error(cube, "Wrong rgb colour format for floor/ceiling!\n");
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r > 255 || color->g > 255 || color->b > 255)
		put_error(cube, "Wrong rgb colour value for floor/ceiling!\n");
	color->rgb = (color->r << 24 | color->g << 16 | color->b << 8 | color->a);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	cube->textures->count++;
	return (0);
}
