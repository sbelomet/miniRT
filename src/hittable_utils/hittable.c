/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:18:00 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/08 16:00:13 by lgosselk         ###   ########.fr       */
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
	t = ft_vec3_dot(ft_vec3_sub(plane->coord, r.origin), unit_norm) / denom;
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

int	ft_hit_cylinder(const void *cylinder_obj, const t_ray r,
	const t_inter ray_t, t_hit_rec *rec)
{
	double		quad[3];
	double		disc;
	t_cylin		*cylin;
	double		root[4];
	double		t;

	cylin = (t_cylin *)cylinder_obj;
	quad[0] = r.dir.x * r.dir.x + r.dir.z * r.dir.z;
	if (fabs(quad[0]) < 1e-8)
		return (false);
	quad[1] = 2 * r.dir.x * (r.origin.x - cylin->coord.x)
		+ 2 * r.dir.z * (r.origin.z - cylin->coord.z);
	quad[2] = pow(r.origin.x - cylin->coord.x, 2)
		+ pow(r.origin.z - cylin->coord.z, 2) - pow(cylin->radius, 2);
	disc = quad[1] * quad[1] - 4 * quad[0] * quad[2];
	if (disc < 1e-8)
		return (false);
	root[0] = (-quad[1] - sqrt(disc)) / (2 * quad[0]);
	root[1] = (-quad[1] + sqrt(disc)) / (2 * quad[0]);
	if (root[0] > root[1])
		ft_swap(&root[0], &root[1]);
	root[2] = r.origin.y + root[0] * r.dir.y;
	root[3] = r.origin.y + root[1] * r.dir.y;
	if (fabs(root[2]) < cylin->height / 2)
		t = root[0];
	if (fabs(root[3]) < cylin->height / 2
		&& root[1] < t)
		t = root[1];
	if (!ft_inter_contains(ray_t, t))
		return (false);
	rec->t = t;
	rec->p = ft_ray_at(r, rec->t);
	rec->normal = ft_set_face_normal(r, ft_vec3_unit(ft_vec3_new(rec->p.x
					- cylin->coord.x, 0, rec->p.z - cylin->coord.z)), rec);
	rec->mat = cylin->mat;
	if (cylin->mat->material == EMMISSIVE)
		rec->emmited = cylin->color;
	else
		rec->emmited = ft_color_new(0, 0, 0, 0);
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
