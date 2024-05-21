/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtform_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:47:37 by scherty           #+#    #+#             */
/*   Updated: 2024/05/21 15:24:08 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_gtform	ft_gtf_mult(const t_gtform g1, const t_gtform g2)
{
	t_gtform	gt;

	gt.fwdtfm = ft_mtrx_mult_mtrx(g1.fwdtfm, g2.fwdtfm);
	gt.bcktfm = ft_mtrx_inverse(gt.fwdtfm);
	return (gt);
}
