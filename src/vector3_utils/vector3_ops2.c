/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_ops2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:54:04 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/04 11:57:30 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_vec3_dot(const t_vector3 v1, const t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3	ft_vec3_cross(const t_vector3 v1, const t_vector3 v2)
{
	t_vector3	res;

	res = ft_vec3_new(0, 0, 0);
	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

double	ft_vec3_len(const t_vector3 v)
{
	return (sqrt(ft_vec3_len_squared(v)));
}

double	ft_vec3_len_squared(const t_vector3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vector3	ft_vec3_unit(t_vector3 v)
{
	double	len;

	len = ft_vec3_len(v);
	if (len != 0)
		return (ft_vec3_div(v, len));
	else
		return (ft_vec3_new(0, 0, 0));
}
