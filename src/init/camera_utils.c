/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:06:19 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/06 11:54:04 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*ft_cam_new(void)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->lookfrom = ft_vec3_new(0, -10, -1);
	cam->lookat = ft_vec3_new(0, 0, 0);
	cam->vup = ft_vec3_new(0, 0, 1);
	cam->length = 2;
	cam->horz_size = .25;
	cam->aspect = 16.0 / 9.0;
	ft_update_cam(cam);
	return (cam);
}

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
