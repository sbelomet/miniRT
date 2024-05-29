/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:34:50 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/29 15:53:08 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_smallest_t(t_equation quad)
{
	int		index;

	quad.min_t = 1e7;
	if (quad.t1 < quad.min_t)
	{
		quad.min_t = quad.t1;
		index = 0;
	}
	if (quad.t2 < quad.min_t)
	{
		quad.min_t = quad.t2;
		index = 1;
	}
	if (quad.t3 < quad.min_t)
	{
		quad.min_t = quad.t3;
		index = 2;
	}
	if (quad.t4 < quad.min_t)
	{
		quad.min_t = quad.t4;
		index = 3;
	}
	return (index);
}

static void	ft_sides_hit(t_equation *quad, t_poi *points,
	const t_ray bck_r, const t_vector3 v)
{
	(*quad).t1 = (-(*quad).b + (*quad).t) / (2 * (*quad).a);
	(*quad).t2 = (-(*quad).b - (*quad).t) / (2 * (*quad).a);
	(*points).poi[0] = ft_vec3_add(bck_r.p1, ft_vec3_mult(v, (*quad).t1));
	(*points).poi[1] = ft_vec3_add(bck_r.p1, ft_vec3_mult(v, (*quad).t2));
	if (((*quad).t1 > 0) && (fabs((*points).poi[0].z) < 1))
		(*points).t_valids[0] = true;
	else
	{
		(*points).t_valids[0] = false;
		(*quad).t1 = 1e8;
	}
	if (((*quad).t2 > 0) && (fabs((*points).poi[1].z) < 1))
		(*points).t_valids[1] = true;
	else
	{
		(*points).t_valids[1] = false;
		(*quad).t2 = 1e8;
	}
}

static void	ft_ends_hit(t_equation *quad, t_poi *points,
	const t_ray bck_r, const t_vector3 v)
{
	(*quad).t3 = (bck_r.p1.z - 1) / -v.z;
	(*quad).t4 = (bck_r.p1.z + 1) / -v.z;
	(*points).poi[2] = ft_vec3_add(bck_r.p1, ft_vec3_mult(v, (*quad).t3));
	(*points).poi[3] = ft_vec3_add(bck_r.p1, ft_vec3_mult(v, (*quad).t4));
	if (((*quad).t3 > 0)
		&& (sqrt(pow((*points).poi[2].x, 2) + pow((*points).poi[2].y, 2)) < 1))
		(*points).t_valids[2] = true;
	else
	{
		(*points).t_valids[2] = false;
		(*quad).t3 = 1e8;
	}
	if (((*quad).t4 > 0)
		&& (sqrt(pow((*points).poi[3].x, 2) + pow((*points).poi[3].y, 2)) < 1))
		(*points).t_valids[3] = true;
	else
	{
		(*points).t_valids[3] = false;
		(*quad).t4 = 1e8;
	}
}
/* 
static void	ft_no_hit()
{
	
} */

static int	ft_rec_setup(t_hit_rec *rec, const t_vector3 end,
	const t_poi points, const t_cylin *cy)
{
	rec->p = ft_gtf_apply_vec3(cy->tm, points.poi[points.index], FWDFORM);
	rec->normal = ft_vec3_unit(ft_vec3_sub(ft_gtf_apply_vec3(
					cy->tm, end, FWDFORM),
				ft_gtf_apply_vec3(cy->tm, ft_vec3_new(0, 0, 0), FWDFORM)));
	rec->color = cy->color;
	rec->mat = cy->mat;
	return (true);
}

int	ft_cylinder_hit(const void *cylinder_obj, const t_ray r, t_hit_rec *rec)
{
	t_cylin		*cy;
	t_ray		bck_r;
	t_vector3	v;
	t_equation	quad;
	t_poi		points;

	cy = (t_cylin *)cylinder_obj;
	bck_r = ft_gtf_apply_ray(cy->tm, r, BCKFORM);
	v = ft_vec3_unit(bck_r.lab);
	quad.a = pow(v.x, 2) + pow(v.y, 2);
	quad.b = 2 * (bck_r.p1.x * v.x + bck_r.p1.y * v.y);
	quad.c = pow(bck_r.p1.x, 2) + pow(bck_r.p1.y, 2) - 1;
	quad.t = sqrt(pow(quad.b, 2) - 4 * quad.a * quad.c);
	if (quad.t > 0)
		ft_sides_hit(&quad, &points, bck_r, v);
	else
	{
		points.t_valids[0] = false;
		points.t_valids[1] = false;
		quad.t1 = 1e8;
		quad.t2 = 1e8;
	}
	if (ft_close_enough(v.z, 0))
	{
		points.t_valids[2] = false;
		points.t_valids[3] = false;
		quad.t3 = 1e8;
		quad.t4 = 1e8;
	}
	else
		ft_ends_hit(&quad, &points, bck_r, v);
	if (!points.t_valids[0] && !points.t_valids[1]
		&& !points.t_valids[2] && !points.t_valids[3])
		return (false);
	points.index = ft_smallest_t(quad);
	if (points.index < 2)
		return (ft_rec_setup(rec, ft_vec3_new(points.poi[points.index].x,
					points.poi[points.index].y, 0), points, cy));
	else
	{
		if (!ft_close_enough(v.z, 0))
		{
			if (sqrt(pow(points.poi[points.index].x, 2)
					+ pow(points.poi[points.index].y, 2)) < 1)
				return (ft_rec_setup(rec, ft_vec3_new(0, 0,
							points.poi[points.index].z), points, cy));
		}
	}
	return (false);
}
