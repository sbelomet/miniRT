/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:07:34 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/14 10:56:45 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* libraries */
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>
# include <limits.h>

/* External libraries */
# include "../mlx/mlx.h"
# include "../libft/includes/libft.h"

/* header files */
# include "enums.h"
# include "macros.h"
# include "structures.h"

/* Funtions prototypes */

/***   UTILS   ***/

/* Parsing utils */
t_color		parse_color(char *arg);
t_vector3	parse_vector(char *arg);
bool		out_range_color(t_color color);
bool		out_range_norm(t_vector3 vector);
bool		out_range(double min, double max, double value);
bool		the_fucking_args_works(t_base *base, char **args, const int type);

/* Parsing utils 2 */
bool		line_regex(char *line);
int			extract_type(char *arg);
bool		only_numbers(char *arg);
bool		right_args(char **args, int type);
t_objects	*get_last_object(t_objects *list);

/* Cleaning */
void		on_destroy(t_base *base);
int			close_window(t_base *base);

/* ---------------- */

/* Init */
t_camera	*ft_cam_new(void);
void		set_base(t_base *base);
int			ft_base_init(t_base *base);
void		ft_update_cam(t_camera *cam);
int			ft_create_image(t_base *base);

/* Errors */
void		*print_error_null(char *error, char *var);
int			print_error(char *error, char *var, int return_val);
int			set_exit_code(t_base *base, int exit_code, int return_val);

/***   PARSING  ***/

/* Parsing file */
int			file_parse(t_base *base, char *filepath);

/* Creating objects */
t_plane		*create_plane(t_base *base, char **args);
t_sphere	*create_sphere(t_base *base, char **args);
t_cylin		*create_cylinder(t_base *base, char **args);
t_cone		*create_cone(t_base *base, char **args);

/* Creating uniques */
bool		add_light(t_base *base, char **args);
t_light		*create_light(t_base *base, char **args);
t_camera	*create_camera(t_base *base, char **args);
t_alight	*create_amblight(t_base *base, char **args);

/* Defaults */
bool		default_uniques(t_base *base);

/* ---------------- */

/* Color */
t_color		ft_color_new(const double a, const double r,
				const double g, const double b);
int			ft_get_color_int(t_color color);
t_color		ft_color_byte_to_per(const t_color color);
void		ft_color_print(const t_color c, const char *name);
t_color		ft_color_add(t_color c1, const t_color c2);
t_color		ft_color_sub(t_color c1, const t_color c2);
t_color		ft_color_mult(t_color c, const double value);
t_color		ft_color_div(t_color c, const double value);
t_color		ft_color_mult_color(t_color c1, const t_color c2);

/* Draw */
void		ft_render(t_base *base);
void		ft_pixel_put(t_base *base, int x, int y, int color);

/* Math Utils */
double		ft_rand_double_range(t_base *base, double min, double max);
double		ft_rand_double(t_base *base);
double		ft_deg_to_rad(double deg);
double		ft_rad_to_deg(double rad);
void		ft_swap(double *a, double *b);
int			ft_close_enough(const double f1, const double f2);

/* Hittable Utils */
int			ft_anything_hit(t_objects *list, const t_ray r, t_hit_rec *rec);
int			ft_sphere_hit(const void *sphere_obj,
				const t_ray r, t_hit_rec *rec);
int			ft_plane_hit(const void *plane_obj, const t_ray r, t_hit_rec *rec);
int			ft_cylinder_hit(const void *cylinder_obj,
				const t_ray r, t_hit_rec *rec);
int			ft_cone_hit(const void *cone_obj, const t_ray r, t_hit_rec *rec);
int			ft_smallest_t(t_equation quad);
void		ft_no_hit(int *t_val_a, int *t_val_b, double *t_a, double *t_b);
void		ft_setup_equa_cylin(const t_ray bck_r,
				t_vector3 *v, t_equation *quad);
void		ft_setup_equa_cone(const t_ray bck_r,
				t_vector3 *v, t_equation *quad);
void		ft_object_add(t_objects **hittable, t_objects *new);

/* Vector3 Utils */
t_vector3	ft_vec3_new(const double x, const double y, const double z);
void		ft_vec3_print(const t_vector3 v, const char *name);
int			ft_vec3_near_zero(const t_vector3 v);
t_vector3	ft_vec3_add(t_vector3 v1, const t_vector3 v2);
t_vector3	ft_vec3_sub(t_vector3 v1, const t_vector3 v2);
t_vector3	ft_vec3_mult(t_vector3 v, const float value);
t_vector3	ft_vec3_div(t_vector3 v, const float value);
t_vector3	ft_vec3_mult_vec3(t_vector3 v1, const t_vector3 v2);
double		ft_vec3_dot(const t_vector3 v1, const t_vector3 v2);
t_vector3	ft_vec3_cross(const t_vector3 v1, const t_vector3 v2);
double		ft_vec3_len(const t_vector3 v);
double		ft_vec3_len_squared(const t_vector3 v);
t_vector3	ft_vec3_unit(t_vector3 v);
int			ft_vec3_grtr(const t_vector3 v1, const t_vector3 v2);
int			ft_vec3_lssr(const t_vector3 v1, const t_vector3 v2);
int			ft_vec3_equal(const t_vector3 v1, const t_vector3 v2);
t_vector3	ft_vec3_negate(t_vector3 vec);

/* Vector4 Utils */
t_vector4	ft_vec4_new(const double x, const double y, const double z,
				const double w);
void		ft_vec4_print(const t_vector4 v, const char *name);
t_vector4	ft_vec4_mult_mtrx(const t_vector4 v, const t_matrix m);

/* Matrix Utils */
t_matrix	ft_mtrx_new(void);
void		ft_mtrx_print(const t_matrix m, const char *name);
t_matrix	ft_mtrx_mult_mtrx(const t_matrix m1, const t_matrix m2);
t_matrix	ft_mtrx_inverse(const t_matrix m);

/* Geometric Transforms Utils */
t_gtform	ft_gtf_new(void);
t_matrix	rotation_z(double rad);
t_matrix	rotation_x(double rad);
t_matrix	rotation_y(double rad);
t_matrix	mtrx_transpose(t_matrix	t);
t_matrix	mtrx_scaling(t_vector3 scale);
t_matrix	mtrx_translate(t_vector3 coord);
t_matrix	rotation_matrix(t_vector3 normal);
t_gtform	ft_gtf_mult(const t_gtform g1, const t_gtform g2);
t_gtform	ft_gtf_new2(const t_matrix fwd, const t_matrix bck);
void		ft_gtf_set_transform(t_gtform *gt, const t_matrix trans,
				const t_matrix rot_mtrx, const t_matrix scale);
t_ray		ft_gtf_apply_ray(const t_gtform gt, const t_ray r,
				const int dir_flag);
t_vector3	ft_gtf_apply_vec3(const t_gtform gt, const t_vector3 v,
				const int dir_flag);

/* Ray Utils */
t_ray		ft_ray_new(const t_vector3 p1, const t_vector3 p2);
int			ft_generate_ray(t_camera cam, double x,
				double y, t_ray *camera_ray);
t_vector3	ft_ray_at(const t_ray ray, const double t);
t_ray		ft_ray_calculate(t_base *base, int i, int j);
t_color		ft_ray_color(t_base *base, t_ray r, int depth, t_objects *world);

/* Intervals Utils */
t_inter		ft_inter_new(const double min, const double max);
t_inter		ft_inter_new2(const t_inter a, const t_inter b);
int			ft_inter_contains(const t_inter inter, const double x);
int			ft_inter_surrounds(const t_inter inter, const double x);
double		ft_inter_clamp(const t_inter inter, const double x);
t_inter		ft_inter_expand(const t_inter inter, const double delta);

/* Material Utils */
t_material	*ft_mat_new(t_base *base, void (*ft_comp_color)
				(t_objects *, t_hit_rec *, t_light *, t_color *));
void		ft_comp_diffuse_color(t_objects *list, t_hit_rec *rec,
				t_light *lights, t_color *result);
t_vector3	ft_reflect(const t_vector3 v, const t_vector3 n);
t_vector3	ft_refract(const t_vector3 uv,
				const t_vector3 n, double etai_over_etat);

/* Scatter Functions */
int			ft_lamb_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);
int			ft_metal_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);
int			ft_dielectric_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);
int			ft_false_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);

/* Axis-Aligned Bounding Boxes Utils */
t_aabb		ft_aabb_new(const t_inter x, const t_inter y, const t_inter z);
t_aabb		ft_aabb_new2(const t_vector3 a, const t_vector3 b);
t_aabb		ft_aabb_new3(const t_aabb box0, const t_aabb box1);
int			ft_aabb_hit(const t_aabb aabb, const t_ray r, t_inter ray_t);

/* Light Utils */
t_vector3	reflect(t_vector3 in, t_vector3 normal);
void		ft_light_add(t_light **light, t_light *new);
bool		ft_dark_spec(t_exposure *exp, t_hit_rec rec, t_light *light);
t_color		ft_add_specular(t_light *light, t_hit_rec rec, t_exposure exp);
int			ft_calc_lights(t_objects *list, t_hit_rec *rec, t_light *lights);

/* ---- Hooks ---- */

/* Translate hook */
t_matrix	to_translate(double x, double y, double z);
bool		translate_cone(t_cone *cone, double x, double y);
bool		translate_light(t_base *base, double x, double y);
bool		translate_camera(t_base *base, double x, double y);
bool		translate_plane(t_plane *plane, double x, double y);
bool		translate_sphere(t_sphere *sphere, double x, double y);
bool		translate_cylinder(t_cylin *cylinder, double x, double y);
void		ft_translate(t_base *base, t_objects *objs, double x, double y);

/* Translate z hook */
bool		trans_z_cone(t_cone *cone, int keycode);
bool		trans_z_light(t_base *base, int keycode);
bool		trans_z_camera(t_base *base, int keycode);
bool		trans_z_plane(t_plane *plane, int keycode);
bool		trans_z_sphere(t_sphere *sphere, int keycode);
bool		trans_z_cylinder(t_cylin *cylinder, int keycode);
void		ft_handle_distance(t_base *base, t_objects *objs, int buttoncode);

/* Modify attributes */
void		modify_value(t_base *base, int type);
bool		add_to_sphere(t_sphere *sphere, int type);
bool		add_to_cone(t_cone *cone, int type, int mode);
bool		add_to_cylinder(t_cylin *cylinder, int type, int mode);

/* Rotation hook */
bool		ft_rotable_keys(int keycode);
t_matrix	ft_new_rotation_matrix(int keycode);
bool		ft_rotation_cone(t_cone *cone, int keycode);
bool		ft_rotation_camera(t_base *base, int keycode);
bool		ft_rotation_plane(t_plane *plane, int keycode);
bool		ft_rotation_cylinder(t_cylin *cylinder, int keycode);
void		ft_rotate(t_base *base, t_objects *objs, int keycode);

/* Mouse hook */
void		ft_setup_selected(t_base *base);
bool		select_object(t_base *base, int x, int y);
void		ft_handle_select(t_base *base, int x, int y);
int			button_hook(int buttoncode, int x, int y, t_base *base);

/* Handle hook */
void		ft_hooks(t_base *base);
void		ft_new_render(t_base *base);
void		ft_handle_light(t_base *base);
void		ft_handle_camera(t_base *base);
void		reset_select(t_base *base, int flag);
bool		ft_check_types(t_base *base, int type);
void		switching_cylin_cone_mode(t_base *base);

#endif