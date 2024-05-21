/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:53:59 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/30 12:51:37 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	*ft_mat_new(int type, t_color albedo, int (*ft_scatter)
	(const t_ray, const t_hit_rec, t_color *, t_ray *))
{
	t_material	*mat;

	mat = (t_material *)malloc(sizeof(t_material));
	mat->material = type;
	mat->albedo = albedo;
	mat->ft_scatter = ft_scatter;
	mat->fuzz = 0;
	mat->ref_index = 1;
	return (mat);
}
