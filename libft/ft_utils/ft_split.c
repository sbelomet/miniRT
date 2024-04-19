/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:06:46 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/18 10:20:40 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_compare(char toCompare, char c)
{
	if (toCompare == c || toCompare == '\0')
		return (1);
	return (0);
}

static int	ft_count_words(char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (!ft_compare(s[i], c) && ft_compare(s[i + 1], c))
			words++;
		i++;
	}
	return (words);
}

static void	ft_push(char *dest, char *src, char c)
{
	int	i;

	i = 0;
	while (!ft_compare(src[i], c))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	ft_logic(char **result, char *s, char c)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	index = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (!ft_compare(s[i + j], c))
				j++;
			result[index] = (char *) malloc((j + 1) * sizeof(char));
			if (result[index] == NULL)
				return (0);
			ft_push(result[index], s + i, c);
			i += j;
			index++;
		}
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{	
	int		i;
	char	*ptr;
	char	**result;
	int		count_words;

	ptr = (char *) s;
	count_words = ft_count_words(ptr, c);
	result = (char **) malloc((count_words + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result[count_words] = 0;
	if (ft_logic(result, ptr, c) != 1)
	{
		i = 0;
		while (result[i])
		{
			free(result[i]);
			i++;
		}
		free(result);
		return (NULL);
	}
	return (result);
}
