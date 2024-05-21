/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:44:09 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/21 15:24:33 by sbelomet         ###   ########.fr       */
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
	return (index);
}

int	ft_cone_hit(const void *cone_obj, const t_ray r, t_hit_rec *rec)
{
	t_cone		*co;
	t_ray		bck_r;
	t_vector3	v;
	t_equation	quad;
	t_vector3	poi[3];
	int			t_valids[3];

	co = (t_cone *)cone_obj;
	bck_r = ft_gtf_apply_ray(co->tm, r, BCKFORM);
	v = ft_vec3_unit(bck_r.lab);
	quad.a = pow(v.x, 2) + pow(v.y, 2) - pow(v.z, 2);
	quad.b = 2 * (bck_r.p1.x * v.x + bck_r.p1.y * v.y - bck_r.p1.z * v.z);
	quad.c = pow(bck_r.p1.x, 2) + pow(bck_r.p1.y, 2) - pow(bck_r.p1.z, 2);
	quad.t = sqrt(pow(quad.b, 2) - 4 * quad.a * quad.c);
	if (quad.t > 0)
	{
		quad.t1 = (-quad.b + quad.t) / (2 * quad.a);
		quad.t2 = (-quad.b - quad.t) / (2 * quad.a);
		poi[0] = ft_vec3_add(bck_r.p1, ft_vec3_mult(v, quad.t1));
		poi[1] = ft_vec3_add(bck_r.p1, ft_vec3_mult(v, quad.t2));
		if ((quad.t1 > 0) && (poi[0].z > 0) && (poi[0].z < 1))
			t_valids[0] = true;
		else
		{
			t_valids[0] = false;
			quad.t1 = 1e8;
		}
		if ((quad.t2 > 0) && (poi[1].z > 0) && (poi[1].z < 1))
			t_valids[1] = true;
		else
		{
			t_valids[1] = false;
			quad.t2 = 1e8;
		}
	}
	else
	{
		t_valids[0] = false;
		t_valids[1] = false;
		quad.t1 = 1e8;
		quad.t2 = 1e8;
	}
	if (ft_close_enough(v.z, 0))
	{
		t_valids[2] = false;
		quad.t3 = 1e8;
	}
	else
	{
		quad.t3 = (bck_r.p1.z - 1) / -v.z;
		poi[2] = ft_vec3_add(bck_r.p1, ft_vec3_mult(v, quad.t3));
		if ((quad.t3 > 0) && (sqrt(pow(poi[2].x, 2) + pow(poi[2].y, 2)) < 1))
			t_valids[2] = true;
		else
		{
			t_valids[2] = false;
			quad.t3 = 1e8;
		}
	}
	if (!t_valids[0] && !t_valids[1] && !t_valids[2])
		return (false);
	int index = ft_smallest_t(quad);
	if (index < 2)
	{
		rec->p = ft_gtf_apply_vec3(co->tm, poi[index], FWDFORM);
		rec->normal = ft_vec3_unit(ft_vec3_sub(ft_gtf_apply_vec3(co->tm,
						ft_vec3_new(poi[index].x, poi[index].y,
							-sqrt(pow(poi[index].x, 2) + pow(poi[index].y, 2))),
						FWDFORM), ft_gtf_apply_vec3(co->tm,
						ft_vec3_new(0, 0, 0), FWDFORM)));
		rec->color = co->color;
		rec->mat = co->mat;
		return (true);
	}
	else
	{
		if (!ft_close_enough(v.z, 0))
		{
			if (sqrt(pow(poi[index].x, 2) + pow(poi[index].y, 2)) < 1)
			{
				rec->p = ft_gtf_apply_vec3(co->tm, poi[index], FWDFORM);
				rec->normal = ft_vec3_unit(ft_vec3_sub(ft_gtf_apply_vec3(co->tm,
								ft_vec3_new(0, 0, poi[index].z), FWDFORM),
							ft_gtf_apply_vec3(co->tm, ft_vec3_new(0, 0, 0),
								FWDFORM)));
				rec->color = co->color;
				rec->mat = co->mat;
				return (true);
			}
		}
	}
	return (false);
}
