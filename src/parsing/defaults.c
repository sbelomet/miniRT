/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:49:22 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/09 14:20:00 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_camera	*default_camera(void)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
		return (print_error_null("Error\n", MALLOC_ERR));
	camera->lookfrom = ft_vec3_new(0, 0, 0);
	camera->lookat = ft_vec3_new(0, 0, 0);
	camera->vfov = 90.0;
	return (camera);
}

static t_alight	*default_amblight(void)
{
	t_alight	*amblight;

	amblight = (t_alight *) malloc(sizeof(t_alight));
	if (!amblight)
		return (print_error_null("Error\n", MALLOC_ERR));
	amblight->ratio = 0.5;
	amblight->color = ft_color_new(0, 125.0, 125.0, 125.0);
	amblight->color = ft_color_byte_to_per(amblight->color);
	return (amblight);
}

/*static t_light	*default_light(void)
{
	t_light		*light;

	light = (t_light *) malloc (sizeof(t_light));
	if (!light)
		return (print_error_null("Error\n", MALLOC_ERR));
	light->coord = ft_vec3_new(-40, 0, -20);
	light->ratio = 0.5;
	light->color = ft_color_new(0, 125.0, 125.0, 125.0);
	light->color = ft_color_byte_to_per(light->color);
	return (light);
}*/

bool	default_uniques(t_base *base)
{
	if (base->camera == NULL)
	{
		base->camera = default_camera();
		if (base->camera == NULL)
			return (false);
	}
	if (base->alight == NULL)
	{
		base->alight = default_amblight();
		if (base->alight == NULL)
			return (false);
	}
	//if (base->light == NULL)
	//{
	//	base->light = default_light();
	//	if (base->light == NULL)
	//		return (false);
	//}
	return (true);
}
