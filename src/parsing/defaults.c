/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:49:22 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/14 10:45:23 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_camera	*default_camera(t_base *base)
{
	t_camera	*cam;

	cam = (t_camera *)ft_malloc(sizeof(t_camera), &base->alloc);
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

static t_alight	*default_amblight(t_base *base)
{
	t_alight	*amblight;

	amblight = (t_alight *)ft_malloc(sizeof(t_alight), &base->alloc);
	if (!amblight)
		return (print_error_null("Error\n", MALLOC_ERR));
	amblight->ratio = 0.5;
	amblight->color = ft_color_new(0, 125.0, 125.0, 125.0);
	amblight->color = ft_color_byte_to_per(amblight->color);
	return (amblight);
}

bool	default_uniques(t_base *base)
{
	if (base->camera == NULL)
	{
		base->camera = default_camera(base);
		if (base->camera == NULL)
			return (false);
	}
	if (base->alight == NULL)
	{
		base->alight = default_amblight(base);
		if (base->alight == NULL)
			return (false);
	}
	return (true);
}
