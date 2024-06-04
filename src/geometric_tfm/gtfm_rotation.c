/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:33:56 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/04 12:00:22 by sbelomet         ###   ########.fr       */
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

/* static void	calculate_rotation_angles(t_vector3 vec, double *x, double *y)
{
	double	ratio;

	ratio = sqrt((vec.x * vec.x) + (vec.z * vec.z));
	if (0.0 == ratio)
		*y = M_PI_2;
	else
		*y = acos(vec.z / ratio);
	*x = acos(ratio);
	printf("ratio: %lf\n", ratio);
	printf("x: %lf\n", *x);
} */

t_matrix	rotation_matrix(t_vector3 normal)
{
/* 	double		x_angle;
	double		y_angle;
	//double		z_angle;
	//t_matrix	rotate_z;
	t_matrix	rotate_y;
	t_matrix	rotate_x; */
	t_matrix	full_rotation;

/* 	//calculate_rotation_angles(normal, &x_angle, &z_angle);
	calculate_rotation_angles(normal, &x_angle, &y_angle);
	//rotate_z = rotation_z(z_angle);
	rotate_y = rotation_y(y_angle);
	ft_mtrx_print(rotate_y, "rotated y");
	rotate_x = rotation_x(x_angle);
	ft_mtrx_print(rotate_x, "rotated x");
	//full_rotation = ft_mtrx_mult_mtrx(rotate_z, rotate_x);
	full_rotation = ft_mtrx_mult_mtrx(rotate_y, rotate_x); */
 	normal = ft_vec3_unit(normal);
	double angle = acos(ft_vec3_dot(ft_vec3_new(0, 0, -1), normal));
	t_vector3 axis = ft_vec3_unit(ft_vec3_cross(ft_vec3_new(0, 0, -1), normal));
	double c = cos(angle);
	double s = sin(angle);
	double t = 1 - c;
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
