/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:06:19 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/14 10:55:03 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_update_cam(t_camera *cam)
{
	cam->alignment = ft_vec3_unit(ft_vec3_sub(cam->lookat, cam->lookfrom));
	if (ft_vec3_equal(cam->alignment, cam->vup)
		|| ft_vec3_equal(cam->alignment, ft_vec3_negate(cam->vup)))
		cam->vup = ft_vec3_new(0, 1, 0);
	cam->proj_screen_u = ft_vec3_unit(ft_vec3_cross(cam->alignment, cam->vup));
	cam->proj_screen_v = ft_vec3_unit(ft_vec3_cross(
				cam->proj_screen_u, cam->alignment));
	cam->proj_screen_center = ft_vec3_add(cam->lookfrom,
			ft_vec3_mult(cam->alignment, cam->length));
	cam->proj_screen_u = ft_vec3_mult(cam->proj_screen_u, cam->horz_size);
	cam->proj_screen_v = ft_vec3_mult(cam->proj_screen_v,
			cam->horz_size / cam->aspect);
}
