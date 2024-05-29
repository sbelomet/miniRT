/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_objs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:05:07 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/29 10:54:27 by sbelomet         ###   ########.fr       */
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
	cylinder->radius = cylinder->diam / 2;
	cylinder->height = ft_atof(args[3]);
	cylinder->color = parse_color(args[4]);
	if (out_range_color(cylinder->color))
		return (free(cylinder), print_error_null("Error\n", RANGE_ERR));
	cylinder->color = ft_color_byte_to_per(cylinder->color);
	cylinder->mat = ft_mat_new(ft_comp_diffuse_color);
	if (!cylinder->mat)
		return (free(cylinder), print_error_null("Error\n", MAT_ERR));
	ft_gtf_set_transform(&cylinder->tm, cylinder->coord, ft_vec3_new(0, 0, 0),
		ft_vec3_new(cylinder->radius, cylinder->radius, cylinder->height));
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
	plane->color = ft_color_byte_to_per(plane->color);
	plane->mat = ft_mat_new(ft_comp_diffuse_color);
	if (!plane->mat)
		return (free(plane), print_error_null("Error\n", MAT_ERR));
	ft_gtf_set_transform(&plane->tm, plane->coord, ft_vec3_new(0, 0, 0),
		ft_vec3_new(99, 99, 1));
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
	sphere->mat = ft_mat_new(ft_comp_diffuse_color);
	if (!sphere->mat)
		return (free(sphere), print_error_null("Error\n", MAT_ERR));
	ft_gtf_set_transform(&sphere->tm, sphere->center, ft_vec3_new(0, 0, 0),
		ft_vec3_new(sphere->radius, sphere->radius, sphere->radius));
	return (sphere);
}

t_cone	*create_cone(char **args)
{
	t_cone	*cone;

	cone = (t_cone *) malloc (sizeof(t_cone));
	if (!cone)
		return (print_error_null("Error\n", MALLOC_ERR));
	cone->coord = parse_vector(args[0]);
	cone->ori = parse_vector(args[1]);
	if (out_range_norm(cone->ori))
		return (free(cone), print_error_null("Error\n", RANGE_ERR));
	cone->diam = ft_atof(args[2]);
	cone->radius = cone->diam / 2;
	cone->height = ft_atof(args[3]);
	cone->color = parse_color(args[4]);
	if (out_range_color(cone->color))
		return (free(cone), print_error_null("Error\n", RANGE_ERR));
	cone->color = ft_color_byte_to_per(cone->color);
	cone->mat = ft_mat_new(ft_comp_diffuse_color);
	if (!cone->mat)
		return (free(cone), print_error_null("Error\n", MAT_ERR));
	ft_gtf_set_transform(&cone->tm, cone->coord, ft_vec3_new(0, 0, 0),
		ft_vec3_new(cone->radius, cone->radius, cone->height));
	return (cone);
}
