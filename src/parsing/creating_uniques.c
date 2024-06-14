/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_uniques.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:08:42 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/14 11:06:19 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*create_light(t_base *base, char **args)
{
	t_light		*light;

	light = (t_light *) ft_malloc(sizeof(t_light), &base->alloc);
	if (!light || !the_fucking_args_works(base, args, LIGHT))
		return (print_error_null("Error\n", CHECK_ERR));
	light->coord = parse_vector(args[0]);
	light->ratio = ft_atof(args[1]);
	if (out_range(0, 1, light->ratio))
		return (print_error_null("Error\n", RANGE_ERR));
	light->ratio /= 200;
	light->color = parse_color(args[2]);
	if (out_range_color(light->color))
		return (print_error_null("Error\n", RANGE_ERR));
	light->intensity = ft_color_mult(light->color, light->ratio);
	light->next = NULL;
	return (light);
}

bool	add_light(t_base *base, char **args)
{
	t_light	*light;

	light = create_light(base, args);
	if (!light)
		return (false);
	ft_light_add(&base->first_light, light);
	base->num_of_lights++;
	return (true);
}

t_camera	*create_camera(t_base *base, char **args)
{
	t_camera	*camera;

	camera = (t_camera *) ft_malloc(sizeof(t_camera), &base->alloc);
	if (!camera || !the_fucking_args_works(base, args, CAMERA))
		return (print_error_null("Error\n", CHECK_ERR));
	camera->lookfrom = parse_vector(args[0]);
	camera->lookat = parse_vector(args[1]);
	camera->vup = ft_vec3_new(0, 0, 1);
	camera->length = 2;
	camera->aspect = 16.0 / 9.0;
	camera->horz_size = (double)ft_atoi(args[2]) / 90;
	if (camera->horz_size < 0 || camera->horz_size > 2)
		return (print_error_null("Error\n", RANGE_ERR));
	ft_update_cam(camera);
	return (camera);
}

t_alight	*create_amblight(t_base *base, char **args)
{
	t_alight	*amblight;

	amblight = (t_alight *) ft_malloc(sizeof(t_alight), &base->alloc);
	if (!amblight || !the_fucking_args_works(base, args, ALIGHT))
		return (print_error_null("Error\n", CHECK_ERR));
	amblight->ratio = ft_atof(args[0]);
	if (out_range(0, 1, amblight->ratio))
		return (print_error_null("Error\n", RANGE_ERR));
	amblight->ratio *= 1.5;
	amblight->color = parse_color(args[1]);
	if (out_range_color(amblight->color))
		return (print_error_null("Error\n", RANGE_ERR));
	amblight->color = ft_color_byte_to_per(amblight->color);
	amblight->intensity = ft_color_mult(amblight->color, amblight->ratio);
	return (amblight);
}
