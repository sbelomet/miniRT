/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_ops1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:53:50 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/28 13:00:59 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	ft_vec3_add(t_vector3 v1, const t_vector3 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vector3	ft_vec3_sub(t_vector3 v1, const t_vector3 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vector3	ft_vec3_mult(t_vector3 v, const float value)
{
	v.x *= value;
	v.y *= value;
	v.z *= value;
	return (v);
}

t_vector3	ft_vec3_div(t_vector3 v, const float value)
{
	v.x /= value;
	v.y /= value;
	v.z /= value;
	return (v);
}

t_vector3	ft_vec3_mult_vec3(t_vector3 v1, const t_vector3 v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return (v1);
}
