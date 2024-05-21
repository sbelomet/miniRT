/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:42:15 by scherty           #+#    #+#             */
/*   Updated: 2024/05/21 15:38:20 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	ft_comp_diffuse_color(t_objects *list, t_hit_rec *rec, t_light *lights)
{
	t_color	diffuse;

	diffuse = ft_color_new(0, 0, 0, 0);
	if (ft_calc_lights(list, rec, lights))
	{
		diffuse = ft_color_mult_color(rec->emmited, rec->color);
	}
	return (diffuse);
}
/* 
t_color	ft_comp_spec_color(t_objects *list, t_hit_rec *rec, t_light *lights)
{
	t_color	spec;

	spec = ft_color_new(0, 0, 0, 0);
	
}
 */