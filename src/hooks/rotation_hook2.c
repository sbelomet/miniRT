/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_hook2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:58:03 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/07 14:17:02 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_rotable_keys(int keycode)
{
	if (keycode == A_KEY || keycode == D_KEY || keycode == S_KEY
		|| keycode == W_KEY || keycode == Z_KEY || keycode == X_KEY)
		return (true);
	return (false);
}

t_matrix	ft_new_rotation_matrix(int keycode)
{
	double		angle;
	t_matrix	new_rotation;

	angle = ft_deg_to_rad(10);
	if (ft_rotable_keys(keycode))
	{
		if (keycode == Z_KEY || keycode == X_KEY)
			new_rotation = rotation_z(angle);
		else if (keycode == S_KEY || keycode == W_KEY)
			new_rotation = rotation_z(angle);
		else if (keycode == A_KEY || keycode == D_KEY)
			new_rotation = rotation_x(angle);
		else
			return (ft_mtrx_new());
		return (new_rotation);
	}
	return (ft_mtrx_new());
}
