/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:18:00 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/24 13:42:43 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_hit_sphere(const t_sphere *sphere, const t_ray r,
	const t_inter ray_t, t_hit_rec *rec)
{
	t_vector3	oc;
	t_vector3	quad;
	double		disc;
	double		root;

	oc = ft_vec3_sub(sphere->center, r.origin);
	quad.x = ft_vec3_len_squared(r.dir);
	quad.y = ft_vec3_dot(r.dir, oc);
	quad.z = ft_vec3_len_squared(oc) - sphere->radius * sphere->radius;
	disc = quad.y * quad.y - quad.x * quad.z;
	if (disc < 0)
		return (false);
	root = (quad.y - sqrt(disc)) / quad.x;
	if (!ft_inter_surrounds(ray_t, root))
	{
		root = (quad.y + sqrt(disc)) / quad.x;
		if (!ft_inter_surrounds(ray_t, root))
			return (false);
	}
	rec->t = root;
	rec->p = ft_ray_at(r, rec->t);
	rec->normal = ft_set_face_normal(r, ft_vec3_div(ft_vec3_sub(rec->p,
					sphere->center), sphere->radius), rec);
	rec->mat = sphere->mat;
	return (true);
}

int	ft_hit_anything(t_hittable *list, const t_ray r,
	const t_inter ray_t, t_hit_rec *rec)
{
	t_hit_rec	temp_rec;
	t_hittable	*temp_hittable;
	int			hit_anything;
	double		closest_so_far;

	temp_hittable = list;
	hit_anything = false;
	closest_so_far = ray_t.max;
	while (temp_hittable)
	{
		if (ft_hit_sphere(temp_hittable->object, r,
				ft_inter_new(ray_t.min, closest_so_far), &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec->normal = temp_rec.normal;
			rec->p = temp_rec.p;
			rec->t = temp_rec.t;
			rec->mat = temp_rec.mat;
		}
		temp_hittable = temp_hittable->next;
	}
	return (hit_anything);
}
