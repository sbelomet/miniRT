/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:08:49 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/30 10:08:51 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	ft_aabb_new(const t_inter x, const t_inter y, const t_inter z)
{
	t_aabb	aabb;

	aabb.x = x;
	aabb.y = y;
	aabb.z = z;
	return (aabb);
}

t_aabb	ft_aabb_new2(const t_vector3 a, const t_vector3 b)
{
	t_aabb	aabb;

	if (a.x <= b.x)
		aabb.x = ft_inter_new(a.x, b.x);
	else
		aabb.x = ft_inter_new(b.x, a.x);
	if (a.y <= b.y)
		aabb.y = ft_inter_new(a.y, b.y);
	else
		aabb.y = ft_inter_new(b.y, a.y);
	if (a.z <= b.z)
		aabb.z = ft_inter_new(a.z, b.z);
	else
		aabb.z = ft_inter_new(b.z, a.z);
	return (aabb);
}

t_aabb	ft_aabb_new3(const t_aabb box0, const t_aabb box1)
{
	t_aabb	aabb;

	aabb.x = ft_inter_new2(box0.x, box1.x);
	aabb.y = ft_inter_new2(box0.y, box1.y);
	aabb.z = ft_inter_new2(box0.z, box1.z);
	return (aabb);
}
