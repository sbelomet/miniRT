/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:23:37 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/30 09:48:31 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_vec3_grtr(const t_vector3 v1, const t_vector3 v2)
{
	if (v1.x > v2.x && v1.y > v2.y && v1.z > v2.z)
		return (true);
	return (false);
}

int	ft_vec3_lssr(const t_vector3 v1, const t_vector3 v2)
{
	if (v1.x < v2.x && v1.y < v2.y && v1.z < v2.z)
		return (true);
	return (false);
}
