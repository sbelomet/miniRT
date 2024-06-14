/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:13:22 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/11 14:33:06 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	out_range(double min, double max, double value)
{
	if (value < min || value > max)
		return (true);
	return (false);
}

bool	out_range_color(t_color color)
{
	if ((color.red < 0 || color.red > 255)
		|| (color.green < 0 || color.green > 255)
		|| (color.blue < 0 || color.blue > 255)
		|| (color.alpha < 0 || color.alpha > 1))
		return (true);
	return (false);
}

bool	out_range_norm(t_vector3 vector)
{
	if ((vector.x < -1 || vector.x > 1) || (vector.y < -1 || vector.y > 1)
		|| (vector.z < -1 || vector.z > 1))
		return (true);
	return (false);
}

t_vector3	parse_vector(char *arg)
{
	int			i;
	t_vector3	vector;
	char		**vectors;

	vectors = ft_split(arg, ',');
	if (!vectors)
		return (ft_vec3_new(0, 0, 0));
	vector.x = ft_atof(vectors[0]);
	vector.y = ft_atof(vectors[1]);
	vector.z = ft_atof(vectors[2]);
	i = -1;
	while (vectors[++i])
		free(vectors[i]);
	free(vectors);
	return (vector);
}

t_color	parse_color(char *arg)
{
	int		i;
	t_color	color;
	char	**colors;

	colors = ft_split(arg, ',');
	if (!colors)
		return (ft_color_new(0, 0, 0, 0));
	color.red = ft_atof(colors[0]);
	color.green = ft_atof(colors[1]);
	color.blue = ft_atof(colors[2]);
	color.alpha = (double)0.0;
	i = -1;
	while (colors[++i])
		free(colors[i]);
	free(colors);
	return (color);
}
