/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:18:00 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/01 15:52:52 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_hit_plane(const void *plane_obj, const t_ray r,
	const t_inter ray_t, t_hit_rec *rec)
{
	t_plane		*plane;
	double		t;
	double		denom;
	t_vector3	unit_norm;

	plane = (t_plane *)plane_obj;
	unit_norm = ft_vec3_unit(plane->norm);
	denom = ft_vec3_dot(unit_norm, r.dir);
	if (fabs(denom) < 1e-8)
		return (false);
	t = (ft_vec3_dot(unit_norm, plane->coord) - ft_vec3_dot(unit_norm, r.origin))
		/ denom;
	if (!ft_inter_contains(ray_t, t))
		return (false);
	rec->t = t;
	rec->p = ft_ray_at(r, t);
	rec->mat = plane->mat;
	rec->normal = ft_set_face_normal(r, unit_norm, rec);
	if (plane->mat->material == EMMISSIVE)
		rec->emmited = plane->color;
	else
		rec->emmited = ft_color_new(0, 0, 0, 0);
	return (true);
}

void	ft_sphere_rec_setup(t_hit_rec *rec, const t_sphere *sphere,
	const t_ray r, const double root)
{
	rec->t = root;
	rec->p = ft_ray_at(r, rec->t);
	rec->normal = ft_set_face_normal(r, ft_vec3_div(ft_vec3_sub(rec->p,
					sphere->center), sphere->radius), rec);
	rec->mat = sphere->mat;
	if (sphere->mat->material == EMMISSIVE)
		rec->emmited = sphere->color;
	else
		rec->emmited = ft_color_new(0, 0, 0, 0);
}

int	ft_hit_sphere(const void *sphere_obj, const t_ray r,
	const t_inter ray_t, t_hit_rec *rec)
{
	t_vector3	oc;
	t_vector3	quad;
	double		disc;
	double		root;
	t_sphere	*sphere;

	sphere = (t_sphere *)sphere_obj;
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
	ft_sphere_rec_setup(rec, sphere, r, root);
	return (true);
}

int	ft_hit_anything(t_objects *list, const t_ray r,
	const t_inter ray_t, t_hit_rec *rec)
{
	t_hit_rec	temp_rec;
	t_objects	*temp_hittable;
	int			hit_anything;
	double		closest_so_far;

	temp_hittable = list;
	hit_anything = false;
	closest_so_far = ray_t.max;
	while (temp_hittable)
	{
		if (temp_hittable->ft_hit(temp_hittable->object, r,
				ft_inter_new(ray_t.min, closest_so_far), &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec->normal = temp_rec.normal;
			rec->p = temp_rec.p;
			rec->t = temp_rec.t;
			rec->mat = temp_rec.mat;
			rec->emmited = temp_rec.emmited;
		}
		temp_hittable = temp_hittable->next;
	}
	return (hit_anything);
}
