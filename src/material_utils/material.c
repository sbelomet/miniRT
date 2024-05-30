/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:53:59 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/30 15:55:38 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	*ft_mat_new(t_base *base, void (*ft_comp_color)
	(t_objects *, t_hit_rec *, t_light *, t_color *))
{
	t_material	*mat;

	mat = (t_material *)ft_malloc(sizeof(t_material), &base->alloc);
	if (!mat)
		return (NULL);
	mat->ft_comp_color = ft_comp_color;
	mat->reflect = 0;
	mat->shine = 400;
    mat->spec = 1;
	return (mat);
}
