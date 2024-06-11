/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:13:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/10 11:00:17 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ft_ray_new(const t_vector3 p1, const t_vector3 p2)
{
	t_ray	ray;

	ray.p1 = p1;
	ray.p2 = p2;
	ray.lab = ft_vec3_sub(p2, p1);
	return (ray);
}

int	ft_generate_ray(t_camera cam, double x, double y, t_ray *camera_ray)
{
	double		world_x;
	double		world_y;
	t_vector3	screen_world_p1;
	t_vector3	screen_world_coord;

	world_x = (x * (1.0 / ((double)WIN_WIDTH / 2.0))) - 1.0;
	world_y = (y * (1.0 / ((double)WIN_HEIGHT / 2.0))) - 1.0;
	screen_world_p1 = ft_vec3_add(cam.proj_screen_center,
			ft_vec3_mult(cam.proj_screen_u, world_x));
	screen_world_coord = ft_vec3_add(screen_world_p1,
			ft_vec3_mult(cam.proj_screen_v, world_y));
	camera_ray->p1 = cam.lookfrom;
	camera_ray->p2 = screen_world_coord;
	camera_ray->lab = ft_vec3_sub(screen_world_coord, cam.lookfrom);
	return (true);
}
