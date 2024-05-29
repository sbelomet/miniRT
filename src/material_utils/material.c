/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:53:59 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/29 11:56:51 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	*ft_mat_new(void (*ft_comp_color)
	(t_objects *, t_hit_rec *, t_light *, t_color *))
{
	t_material	*mat;

	mat = (t_material *)malloc(sizeof(t_material));
	if (!mat)
		return (NULL);
	mat->ft_comp_color = ft_comp_color;
	mat->reflect = 0;
	mat->shine = 0;
	return (mat);
}
