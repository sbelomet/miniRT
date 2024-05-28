/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:49:22 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_camera	*default_camera(void)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		return (print_error_null("Error\n", MALLOC_ERR));
	cam->lookfrom = ft_vec3_new(0, -10, -1);
	cam->lookat = ft_vec3_new(0, 0, 0);
	cam->vup = ft_vec3_new(0, 0, 1);
	cam->length = 2;
	cam->horz_size = .25;
	cam->aspect = 16.0 / 9.0;
	ft_update_cam(cam);
	return (cam);
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

/* static t_light	*default_light(void)
{
	t_light		*light;

	light = (t_light *) malloc (sizeof(t_light));
	if (!light)
		return (print_error_null("Error\n", MALLOC_ERR));
	light->coord = ft_vec3_new(0, -10, -2);
	light->ratio = 0.5;
	light->color = ft_color_new(0, 125.0, 125.0, 125.0);
	light->color = ft_color_byte_to_per(light->color);
	light->next = NULL;
	return (light);
} */

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
/* 	if (base->first_light == NULL)
	{
		base->first_light = default_light();
		if (base->first_light == NULL)
			return (false);
	} */
	return (true);
}
