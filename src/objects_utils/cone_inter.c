/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:44:09 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/30 12:00:02 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_sides_hit(t_equation *quad, t_poi *points,
	const t_ray bck_r, const t_vector3 v)
{
	(*quad).t1 = (-(*quad).b + (*quad).t) / (2 * (*quad).a);
	(*quad).t2 = (-(*quad).b - (*quad).t) / (2 * (*quad).a);
	(*points).poi[0] = ft_vec3_add(bck_r.p1, ft_vec3_mult(v, (*quad).t1));
	(*points).poi[1] = ft_vec3_add(bck_r.p1, ft_vec3_mult(v, (*quad).t2));
	if (((*quad).t1 > 0) && ((*points).poi[0].z > 0)
		& ((*points).poi[0].z < 1))
		(*points).tv[0] = true;
	else
	{
		(*points).tv[0] = false;
		(*quad).t1 = 1e8;
	}
	if (((*quad).t2 > 0) && ((*points).poi[1].z > 0)
		&& ((*points).poi[1].z < 1))
		(*points).tv[1] = true;
	else
	{
		(*points).tv[1] = false;
		(*quad).t2 = 1e8;
	}
}

static void	ft_ends_hit(t_equation *quad, t_poi *points,
	const t_ray bck_r, const t_vector3 v)
{
	(*quad).t3 = (bck_r.p1.z - 1) / -v.z;
	(*points).poi[2] = ft_vec3_add(bck_r.p1, ft_vec3_mult(v, (*quad).t3));
	if (((*quad).t3 > 0)
		&& (sqrt(pow((*points).poi[2].x, 2) + pow((*points).poi[2].y, 2)) < 1))
		(*points).tv[2] = true;
	else
	{
		(*points).tv[2] = false;
		(*quad).t3 = 1e8;
	}
}

static int	ft_sides_rec_setup(t_hit_rec *rec,
	const t_poi points, const t_cone *co)
{
	rec->p = ft_gtf_apply_vec3(co->tm, points.poi[points.index], FWDFORM);
	rec->normal = ft_vec3_unit(ft_vec3_sub(ft_gtf_apply_vec3(
					co->tm, ft_vec3_new(points.poi[points.index].x,
						points.poi[points.index].y,
						-sqrt(pow(points.poi[points.index].x, 2)
							+ pow(points.poi[points.index].y, 2))), FWDFORM),
				ft_gtf_apply_vec3(co->tm, ft_vec3_new(0, 0, 0), FWDFORM)));
	rec->color = co->color;
	rec->mat = co->mat;
	return (true);
}

static int	ft_ends_rec_setup(t_hit_rec *rec, const t_poi points,
	const t_cone *co, const t_vector3 v)
{
	if (!ft_close_enough(v.z, 0))
	{
		if (sqrt(pow(points.poi[points.index].x, 2)
				+ pow(points.poi[points.index].y, 2)) < 1)
		{
			rec->p = ft_gtf_apply_vec3(co->tm,
					points.poi[points.index], FWDFORM);
			rec->normal = ft_vec3_unit(ft_vec3_sub(ft_gtf_apply_vec3(co->tm,
							ft_vec3_new(0, 0, points.poi[points.index].z),
							FWDFORM),
						ft_gtf_apply_vec3(co->tm, ft_vec3_new(0, 0, 0),
							FWDFORM)));
			rec->color = co->color;
			rec->mat = co->mat;
			return (true);
		}
	}
	return (false);
}

int	ft_cone_hit(const void *cone_obj, const t_ray r, t_hit_rec *rec)
{
	t_cone		*co;
	t_ray		bck_r;
	t_vector3	v;
	t_equation	quad;
	t_poi		points;

	co = (t_cone *)cone_obj;
	bck_r = ft_gtf_apply_ray(co->tm, r, BCKFORM);
	ft_setup_equa_cone(bck_r, &v, &quad);
	if (quad.t > 0)
		ft_sides_hit(&quad, &points, bck_r, v);
	else
		ft_no_hit(&points.tv[0], &points.tv[1], &quad.t1, &quad.t2);
	if (ft_close_enough(v.z, 0))
		ft_no_hit(&points.tv[2], &points.tv[3], &quad.t3, &quad.t4);
	else
		ft_ends_hit(&quad, &points, bck_r, v);
	if (!points.tv[0] && !points.tv[1] && !points.tv[2])
		return (false);
	points.index = ft_smallest_t(quad);
	if (points.index < 2)
		return (ft_sides_rec_setup(rec, points, co));
	else
		return (ft_ends_rec_setup(rec, points, co, v));
	return (false);
}
