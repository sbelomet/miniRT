/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:00:23 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/30 10:01:37 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	ft_aabb_axis_inter(const t_aabb aabb, const int n)
{
	if (n == 1)
		return (aabb.y);
	if (n == 2)
		return (aabb.z);
	return (aabb.x);
}

void	ft_aabb_calc_inter(const double *t, t_inter *ray_t)
{
	if (t[0] < t[1])
	{
		if (t[0] > ray_t->min)
			ray_t->min = t[0];
		if (t[1] < ray_t->max)
			ray_t->max = t[1];
	}
	else
	{
		if (t[1] > ray_t->min)
			ray_t->min = t[1];
		if (t[0] < ray_t->max)
			ray_t->max = t[0];
	}
}

int	ft_aabb_hit(const t_aabb aabb, const t_ray r, t_inter ray_t)
{
	int		axis;
	t_inter	ax;
	double	ad_inv;
	double	t[2];

	axis = -1;
	while (++axis < 3)
	{
		ax = ft_aabb_axis_inter(aabb, axis);
		ad_inv = 1.0 / ft_vec3_get(r.dir, axis);
		t[0] = (ax.min - ft_vec3_get(r.origin, axis)) * ad_inv;
		t[1] = (ax.max - ft_vec3_get(r.origin, axis)) * ad_inv;
		ft_aabb_calc_inter(t, &ray_t);
		if (ray_t.max <= ray_t.min)
			return (false);
	}
	return (true);
}
