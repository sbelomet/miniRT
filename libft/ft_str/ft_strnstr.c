/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:22:21 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/18 10:20:31 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	if (*needle == '\0')
		return ((char *) haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[i + j] && needle[j]
				&& haystack[i + j] == needle[j] && (i + j) < len)
				j++;
			if (needle[j] == '\0')
				return ((char *) haystack + i);
		}
		i++;
	}
	return (NULL);
}
