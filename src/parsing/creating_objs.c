/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_objs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:05:07 by lgosselk          #+#    #+#             */
/*   Updated: 2024/04/30 11:36:40 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylin	*create_cylinder(char **args)
{
	t_cylin	*cylinder;

	cylinder = (t_cylin *) malloc (sizeof(t_cylin));
	if (!cylinder)
		return (print_error_null("Error\n", MALLOC_ERR));
	cylinder->coord = parse_vector(args[0]);
	cylinder->ori = parse_vector(args[1]);
	if (out_range_norm(cylinder->ori))
		return (free(cylinder), print_error_null("Error\n", RANGE_ERR));
	cylinder->diam = ft_atof(args[2]);
	cylinder->height = ft_atof(args[3]);
	cylinder->color = parse_color(args[4]);
	if (out_range_color(cylinder->color))
		return (free(cylinder), print_error_null("Error\n", RANGE_ERR));
	return (cylinder);
}

t_plane	*create_plane(char **args)
{
	t_plane	*plane;

	plane = (t_plane *) malloc (sizeof(t_plane));
	if (!plane)
		return (print_error_null("Error\n", MALLOC_ERR));
	plane->coord = parse_vector(args[0]);
	plane->norm = parse_vector(args[1]);
	if (out_range_norm(plane->norm))
		return (free(plane), print_error_null("Error\n", RANGE_ERR));
	plane->color = parse_color(args[2]);
	if (out_range_color(plane->color))
		return (free(plane), print_error_null("Error\n", RANGE_ERR));
	return (plane);
}

t_sphere	*create_sphere(char **args)
{
	t_sphere	*sphere;

	sphere = (t_sphere *) malloc (sizeof(t_sphere));
	if (!sphere)
		return (print_error_null("Error\n", MALLOC_ERR));
	sphere->center = parse_vector(args[0]);
	sphere->diam = ft_atof(args[1]);
	sphere->radius = sphere->diam / 2;
	sphere->color = parse_color(args[2]);
	if (out_range_color(sphere->color))
		return (free(sphere), print_error_null("Error\n", RANGE_ERR));
	sphere->color = ft_color_byte_to_per(sphere->color);
	sphere->mat = ft_mat_new(LAMBERTIAN, sphere->color, ft_lamb_scatter);
	return (sphere);
}
