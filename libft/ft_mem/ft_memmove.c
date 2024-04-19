/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:36:50 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/18 10:22:49 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*cp_src;
	unsigned char	*cp_dest;

	if (!dest && !src)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, len));
	cp_dest = (unsigned char *) dest;
	cp_src = (unsigned char *) src;
	while (len--)
		cp_dest[len] = cp_src[len];
	return (dest);
}
