/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:35:50 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/06 11:12:49 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_rec_setup(t_hit_rec *rec, const t_equation quad,
	const t_ray bck_r, const t_sphere *sp)
{
	t_vector3	vhat;
	t_vector3	origin;

	vhat = ft_vec3_unit(bck_r.lab);
	if (quad.t1 < quad.t2)
		rec->p = ft_vec3_add(bck_r.p1, ft_vec3_mult(vhat, quad.t1));
	else
		rec->p = ft_vec3_add(bck_r.p1, ft_vec3_mult(vhat, quad.t2));
	rec->p = ft_gtf_apply_vec3(sp->tm, rec->p, FWDFORM);
	origin = ft_gtf_apply_vec3(sp->tm, ft_vec3_new(0, 0, 0), FWDFORM);
	rec->normal = ft_vec3_unit(ft_vec3_sub(rec->p, origin));
	rec->color = sp->color;
	rec->mat = sp->mat;
}

int	ft_sphere_hit(const void *sphere_obj, const t_ray r, t_hit_rec *rec)
{
	t_sphere	*sp;
	t_equation	quad;
	t_ray		bck_r;

	sp = (t_sphere *)sphere_obj;
	bck_r = ft_gtf_apply_ray(sp->tm, r, BCKFORM);
	quad.a = 1;
	quad.b = 2 * ft_vec3_dot(bck_r.p1, ft_vec3_unit(bck_r.lab));
	quad.c = ft_vec3_dot(bck_r.p1, bck_r.p1) - 1;
	quad.t = quad.b * quad.b - 4 * quad.a * quad.c;
	if (quad.t > 0)
	{
		quad.t = sqrt(quad.t);
		quad.t1 = (-quad.b + quad.t) / 2.0;
		quad.t2 = (-quad.b - quad.t) / 2.0;
		if (quad.t1 < 0 || quad.t2 < 0)
			return (false);
		else
			ft_rec_setup(rec, quad, bck_r, sp);
		return (true);
	}
	return (false);
}
