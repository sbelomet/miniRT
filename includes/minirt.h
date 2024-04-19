/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:07:34 by lgosselk          #+#    #+#             */
/*   Updated: 2024/04/19 15:16:32 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

/* Libraries External */
# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"

# define TITLE "BetterBlender"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

/* Definitions */

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}				t_vector3;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

/* Objects structures */

typedef struct s_alight
{
	double	ratio;
	t_color	color;
}				t_alight;

typedef struct s_camera
{
	t_vector3	coord;
	t_vector3	ori;
	int			fov;
}				t_camera;

typedef struct s_light
{
	t_vector3	coord;
	double		ratio;
	t_color		color;
}				t_light;

typedef struct s_sphere
{
	t_vector3	coord;
	double		diam;
	t_color		color;
}				t_sphere;

typedef struct s_plane
{
	t_vector3	coord;
	t_vector3	norm;
	t_color		color;
}				t_plane;

typedef struct s_cylin
{
	t_vector3	coord;
	t_vector3	ori;
	double		diam;
	double		height;
	t_color		color;
}				t_cylin;

typedef struct s_token
{
	void			*object;
	char			*type;
	struct s_token	*next;
}				t_token;

/* Base */

typedef struct s_base
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		size_line;
	int		bitsperpix;
	int		endian;
	t_token	*first_token;
}				t_base;

/* Errors */
void	ft_error(char *message);

/* Color */
int		ft_get_color(double a, double r, double g, double b);

/* Draw */
void	ft_pixel_put(t_base *base, int x, int y, int color);
void	ft_draw_base_texture(t_base *base);

#endif