/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:42:15 by scherty           #+#    #+#             */
/*   Updated: 2024/06/04 13:48:23 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_comp_diffuse_color(t_objects *list, t_hit_rec *rec, t_light *lights,
	t_color *result)
{
	ft_calc_lights(list, rec, lights);
	rec->emmited = ft_color_add(rec->emmited, ft_color_mult(
				rec->base->alight->color, rec->base->alight->ratio));
	*result = ft_color_mult_color(rec->emmited, rec->color);
}
