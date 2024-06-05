/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:11:35 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/05 15:19:07 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_rec_setup(t_hit_rec *rec, t_objects *object,
	const t_hit_rec tmp_rec, const t_ray r)
{
	rec->object = object;
	rec->p = tmp_rec.p;
	rec->eyev = ft_vec3_negate(ft_vec3_unit(r.lab));
	if (ft_vec3_dot(tmp_rec.normal, rec->eyev) < 0)
		rec->normal = ft_vec3_mult(tmp_rec.normal, -1);
	else
		rec->normal = tmp_rec.normal;
	rec->color = tmp_rec.color;
	rec->mat = tmp_rec.mat;
}

int	ft_anything_hit(t_objects *list, const t_ray r, t_hit_rec *rec)
{
	t_objects	*tmp_list;
	t_hit_rec	tmp_rec;
	int			hit_anything;
	double		min_dist;

	tmp_list = list;
	hit_anything = false;
	min_dist = 1e6;
	while (tmp_list)
	{
		if (tmp_list->ft_hit(tmp_list->object, r, &tmp_rec))
		{
			if (ft_vec3_len_squared(ft_vec3_sub(tmp_rec.p, r.p1)) < min_dist)
			{
				min_dist = ft_vec3_len_squared(ft_vec3_sub(tmp_rec.p, r.p1));
				hit_anything = true;
				ft_rec_setup(rec, tmp_list, tmp_rec, r);
			}
		}
		tmp_list = tmp_list->next;
	}
	return (hit_anything);
}
