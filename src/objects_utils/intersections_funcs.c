/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:11:35 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/21 15:35:11 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
				rec->object = tmp_list;
				rec->p = tmp_rec.p;
				rec->normal = tmp_rec.normal;
				rec->color = tmp_rec.color;
				rec->mat = tmp_rec.mat;
			}
		}
		tmp_list = tmp_list->next;
	}
	return (hit_anything);
}
