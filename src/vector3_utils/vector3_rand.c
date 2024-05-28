/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_rand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:15:50 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/* 
t_vector3	ft_vec3_rand(t_base *base)
{
	return (ft_vec3_new(ft_rand_double(base), ft_rand_double(base),
			ft_rand_double(base)));
}

t_vector3	ft_vec3_rand_range(t_base *base, const double min, const double max)
{
	return (ft_vec3_new(ft_rand_double_range(base, min, max),
			ft_rand_double_range(base, min, max),
			ft_rand_double_range(base, min, max)));
}

t_vector3	ft_vec3_rand_unit_sphere(t_base *base)
{
	t_vector3	p;

	while (true)
	{
		p = ft_vec3_rand_range(base, -1, 1);
		if (ft_vec3_len_squared(p) < 1)
			return (p);
	}
}

t_vector3	ft_vec3_rand_unit(t_base *base)
{
	return (ft_vec3_unit(ft_vec3_rand_unit_sphere(base)));
}

t_vector3	ft_vec3_rand_hemis(t_base *base, const t_vector3 normal)
{
	t_vector3	on_unit_sphere;

	on_unit_sphere = ft_vec3_rand_unit(base);
	if (ft_vec3_dot(on_unit_sphere, normal) > 0.0)
		return (on_unit_sphere);
	return (ft_vec3_mult(on_unit_sphere, -1));
} */
