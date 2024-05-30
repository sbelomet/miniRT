/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:33:56 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/30 12:00:50 by sbelomet         ###   ########.fr       */
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

static void	calculate_rotation_angles(t_vector3 vec, double *x, double *z)
{
	double	ratio;

	ratio = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (0.0 == ratio)
		*z = M_PI_2;
	else
		*z = acos(vec.y / ratio);
	*x = acos(ratio);
}

t_matrix	rotation_matrix(t_vector3 normal)
{
	double		x_angle;
	double		z_angle;
	t_matrix	rotate_z;
	t_matrix	rotate_x;
	t_matrix	full_rotation;

	calculate_rotation_angles(normal, &x_angle, &z_angle);
	rotate_z = rotation_z(z_angle);
	rotate_x = rotation_x(x_angle);
	full_rotation = ft_mtrx_mult_mtrx(rotate_z, rotate_x);
	return (full_rotation);
}
