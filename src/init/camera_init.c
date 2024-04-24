/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:12:53 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/24 15:12:46 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	ft_camera_init2(double vfov)
{
	t_camera	cam;
	double		theta;
	double		h;

	cam.vfov = vfov;
	cam.lookfrom = ft_vec3_new(-2, 2, 1);
	cam.lookat = ft_vec3_new(0, 0, -1);
	cam.vup = ft_vec3_new(0, 1, 0);
	cam.focal_length = ft_vec3_len(ft_vec3_sub(cam.lookfrom, cam.lookat));
	theta = ft_deg_to_rad(cam.vfov);
	h = tan(theta / 2);
	cam.viewport_height = 2 * h * cam.focal_length;
	cam.viewport_width = cam.viewport_height * ((double)WIN_WIDTH / WIN_HEIGHT);
	return (cam);
}

t_camera	ft_camera_init(double vfov)
{
	t_camera	cam;
	t_vector3	basis_vecs[3];
	t_vector3	viewport_uv[2];
	t_vector3	viewport_upper_left;

	cam = ft_camera_init2(vfov);
	basis_vecs[2] = ft_vec3_unit(ft_vec3_sub(cam.lookfrom, cam.lookat));
	basis_vecs[0] = ft_vec3_unit(ft_vec3_cross(cam.vup, basis_vecs[2]));
	basis_vecs[1] = ft_vec3_cross(basis_vecs[2], basis_vecs[0]);
	viewport_uv[0] = ft_vec3_mult(basis_vecs[0], cam.viewport_width);
	viewport_uv[1] = ft_vec3_mult(ft_vec3_mult(basis_vecs[1], -1),
			cam.viewport_height);
	cam.pixel_delta_u = ft_vec3_div(viewport_uv[0], WIN_WIDTH);
	cam.pixel_delta_v = ft_vec3_div(viewport_uv[1], WIN_HEIGHT);
	viewport_upper_left = ft_vec3_sub(ft_vec3_sub(ft_vec3_sub(cam.lookfrom,
					ft_vec3_mult(basis_vecs[2], cam.focal_length)), ft_vec3_div(
					viewport_uv[0], 2)), ft_vec3_div(viewport_uv[1], 2));
	cam.pixel00_loc = ft_vec3_add(ft_vec3_mult(ft_vec3_add(
					cam.pixel_delta_u, cam.pixel_delta_v), .5),
			viewport_upper_left);
	cam.ori = ft_vec3_new(0, 0, cam.focal_length);
	return (cam);
}
