/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:34:04 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_plane_hit(const void *plane_obj, const t_ray r, t_hit_rec *rec)
{
	t_plane		*pl;
	t_ray		bck_r;
	t_vector3	k;
	double		t;
	double		uv[2];

	pl = (t_plane *)plane_obj;
	bck_r = ft_gtf_apply_ray(pl->tm, r, BCKFORM);
	k = ft_vec3_unit(bck_r.lab);
	if (!ft_close_enough(k.z, 0))
	{
		t = bck_r.p1.z / -k.z;
		if (t > 0)
		{
			uv[0] = bck_r.p1.x + (k.x * t);
			uv[1] = bck_r.p1.y + (k.y * t);
			if ((fabs(uv[0]) < 1) && (fabs(uv[1]) < 1))
			{
				rec->p = ft_vec3_add(bck_r.p1, ft_vec3_mult(k, t));
				rec->p = ft_gtf_apply_vec3(pl->tm, rec->p, FWDFORM);
				rec->normal = ft_vec3_unit(ft_vec3_sub(ft_gtf_apply_vec3(pl->tm,
								ft_vec3_new(0, 0, -1), FWDFORM),
							ft_gtf_apply_vec3(pl->tm, ft_vec3_new(0, 0, 0),
								FWDFORM)));
				rec->color = pl->color;
				rec->mat = pl->mat;
				return (true);
			}
		}
	}
	return (false);
}
