/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:13:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/23 15:41:43 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ft_ray_new(const t_vector3 origin, const t_vector3 dir)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = dir;
	return (ray);
}

t_vector3	ft_ray_at(const t_ray ray, const double t)
{
	return (ft_vec3_add(ray.origin, ft_vec3_mult(ray.dir, t)));
}

t_ray	ft_ray_calculate(t_base *base, int i, int j)
{
	t_vector3	offset;
	t_vector3	pixel_sample;
	t_vector3	ray_origin;
	t_vector3	ray_direction;

	offset = ft_vec3_new(0, 0, 0);
	offset = ft_vec3_new(ft_rand_double(base) - .5,
			ft_rand_double(base) - .5, 0);
	pixel_sample = ft_vec3_add(base->camera.pixel00_loc, ft_vec3_add(
				ft_vec3_mult(base->camera.pixel_delta_u, i + offset.x),
				ft_vec3_mult(base->camera.pixel_delta_v, j + offset.y)));
	ray_origin = base->camera.origin;
	ray_direction = ft_vec3_sub(pixel_sample, ray_origin);
	return (ft_ray_new(ray_origin, ray_direction));
}

t_color	ft_ray_color(t_base *base, t_ray r, int depth, t_hittable *world)
{
	t_hit_rec	rec;
	t_vector3	unit_direction;
	t_vector3	direction;
	double		a;

	if (depth <= 0)
		return (ft_color_new(0, 0, 0, 0));
	rec.normal = ft_vec3_new(0, 0, 0);
	if (ft_hit_anything(world, r, ft_inter_new(0.001, INFINITY), &rec))
	{
		direction = ft_vec3_add(rec.normal,
				ft_vec3_rand_hemis(base, rec.normal));
		return (ft_color_mult(ft_ray_color(base,
					ft_ray_new(rec.p, direction), depth - 1, world), .5));
	}
	else
	{
		unit_direction = ft_vec3_unit(r.dir);
		a = .5 * (unit_direction.x + 1.0);
		return (ft_color_add(ft_color_mult(ft_color_new(0, .9, 0, .6), 1.0 - a),
				ft_color_mult(ft_color_new(0, 0, .2, .7), a)));
	}
}

/* 
		return (ft_color_mult(ft_color_new(0, rec.normal.x + 1,
					rec.normal.y + 1, rec.normal.z + 1), .5)); */
