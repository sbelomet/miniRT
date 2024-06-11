/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:34:04 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/06 10:46:52 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_rec_setup(t_hit_rec *rec, const t_vector3 kxt,
	const t_ray bck_r, const t_plane *pl)
{
	rec->p = ft_vec3_add(bck_r.p1, kxt);
	rec->p = ft_gtf_apply_vec3(pl->tm, rec->p, FWDFORM);
	rec->normal = ft_vec3_unit(ft_vec3_sub(ft_gtf_apply_vec3(pl->tm,
					ft_vec3_new(0, 0, -1), FWDFORM),
				ft_gtf_apply_vec3(pl->tm, ft_vec3_new(0, 0, 0),
					FWDFORM)));
	rec->color = pl->color;
	rec->mat = pl->mat;
}

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
				ft_rec_setup(rec, ft_vec3_mult(k, t), bck_r, pl);
				return (true);
			}
		}
	}
	return (false);
}
