/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:40:55 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/30 11:59:12 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_smallest_t(t_equation quad)
{
	int		index;

	quad.min_t = 1e7;
	if (quad.t1 < quad.min_t)
	{
		quad.min_t = quad.t1;
		index = 0;
	}
	if (quad.t2 < quad.min_t)
	{
		quad.min_t = quad.t2;
		index = 1;
	}
	if (quad.t3 < quad.min_t)
	{
		quad.min_t = quad.t3;
		index = 2;
	}
	if (quad.t4 < quad.min_t)
	{
		quad.min_t = quad.t4;
		index = 3;
	}
	return (index);
}

void	ft_no_hit(int *t_val_a, int *t_val_b, double *t_a, double *t_b)
{
	*t_val_a = false;
	*t_val_b = false;
	*t_a = 1e8;
	*t_b = 1e8;
}

void	ft_setup_equa_cylin(const t_ray bck_r,
	t_vector3 *v, t_equation *quad)
{
	*v = ft_vec3_unit(bck_r.lab);
	(*quad).a = pow((*v).x, 2) + pow((*v).y, 2);
	(*quad).b = 2 * (bck_r.p1.x * (*v).x + bck_r.p1.y * (*v).y);
	(*quad).c = pow(bck_r.p1.x, 2) + pow(bck_r.p1.y, 2) - 1;
	(*quad).t = sqrt(pow((*quad).b, 2) - 4 * (*quad).a * (*quad).c);
}

void	ft_setup_equa_cone(const t_ray bck_r,
	t_vector3 *v, t_equation *quad)
{
	*v = ft_vec3_unit(bck_r.lab);
	(*quad).a = pow((*v).x, 2) + pow((*v).y, 2) - pow((*v).z, 2);
	(*quad).b = 2 * (bck_r.p1.x * (*v).x + bck_r.p1.y * (*v).y
			- bck_r.p1.z * (*v).z);
	(*quad).c = pow(bck_r.p1.x, 2) + pow(bck_r.p1.y, 2) - pow(bck_r.p1.z, 2);
	(*quad).t = sqrt(pow((*quad).b, 2) - 4 * (*quad).a * (*quad).c);
	(*quad).t4 = 1e8;
}
