/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:33:56 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 12:40:45 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	rotation_x(double rad)
{
	t_matrix	table;

	table = ft_mtrx_new();
	table.m[1][1] = cos(rad);
	table.m[1][2] = -sin(rad);
	table.m[2][1] = sin(rad);
	table.m[2][2] = cos(rad);
	return (table);
}

t_matrix	rotation_y(double rad)
{
	t_matrix	table;

	table = ft_mtrx_new();
	table.m[0][0] = cos(rad);
	table.m[0][2] = sin(rad);
	table.m[2][0] = -sin(rad);
	table.m[2][2] = cos(rad);
	return (table);
}

t_matrix	rotation_z(double rad)
{
	t_matrix	table;

	table = ft_mtrx_new();
	table.m[0][0] = cos(rad);
	table.m[0][1] = -sin(rad);
	table.m[1][0] = sin(rad);
	table.m[1][1] = cos(rad);
	return (table);
}

t_matrix	rotation_matrix(t_vector3 normal)
{
	t_matrix	full_rotation;
	t_vector3	axis;
	double		c;
	double		s;
	double		t;

	normal = ft_vec3_unit(normal);
	axis = ft_vec3_unit(ft_vec3_cross(ft_vec3_new(0, 0, -1), normal));
	c = cos(acos(ft_vec3_dot(ft_vec3_new(0, 0, -1), normal)));
	s = sin(acos(ft_vec3_dot(ft_vec3_new(0, 0, -1), normal)));
	t = 1 - c;
	full_rotation = ft_mtrx_new();
	full_rotation.m[0][0] = c + pow(axis.x, 2) * t;
	full_rotation.m[0][1] = axis.x * axis.y * t - axis.z * s;
	full_rotation.m[0][2] = axis.x * axis.z * t + axis.y * s;
	full_rotation.m[1][0] = axis.y * axis.x * t + axis.z * s;
	full_rotation.m[1][1] = c + pow(axis.y, 2) * t;
	full_rotation.m[1][2] = axis.y * axis.z * t - axis.x * s;
	full_rotation.m[2][0] = axis.z * axis.x * t - axis.y * s;
	full_rotation.m[2][1] = axis.z * axis.y * t + axis.x * s;
	full_rotation.m[2][2] = c + pow(axis.z, 2) * t;
	return (full_rotation);
}
