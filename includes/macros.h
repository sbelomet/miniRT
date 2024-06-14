/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:40:34 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/14 11:04:13 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/* General macros */
# define MAX_DEPTH 10
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define EPSILON 0.0001
# define SAMPLE_PPIXEL 40
# define PIX_SAMPLE_SCALE 0.025

/* Keyboard mapping macros */
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define Z_KEY 6
# define X_KEY 7
# define W_KEY 13
# define TAB_KEY 48
# define ESC_KEY 53
# define PLUS_KEY 69
# define ARROW_UP 126
# define MINUS_KEY 78
# define RENDER_KEY 76
# define ARROW_DOWN 125
# define DESELECT_KEY 36
# define LIGHT_SELECT 19
# define CAMERA_SELECT 18
# define CONTROL_LEFT 256
# define CONTROL_RIGHT 269

/* Mouse mapping macros */
# define CLICK_LEFT 1

/* Normal/inverse matrix */
# define FWDFORM 1
# define BCKFORM 0

/* Error macros */
# define TITLE "BetterBlender"
# define MALLOC_ERR "Malloc error"
# define EXT_ERR "Invalid extension file"
# define BAD_ARGS "Bad number of arguments"
# define MLX_ERR "MLX initialisation failure"
# define IMG_ERR "Image initialisation failure"
# define CAM_ERR "Camera initialisation failure"
# define WIN_ERR "Window initialisation failure"
# define MAT_ERR "Material initialisation failure"
# define ISS_ERR "Whitespace that is not a space detected"
# define OBJNAME_ERR "Invalid object name while parsing file"
# define REGEX_ERR "File contains forbidden characters"
# define CHECK_ERR "Malloc error or an argument is not complete"
# define ARGS_ERR "Bad number of arguments while parsing an object"
# define RANGE_ERR "A number, while parsing the file is out of range"
# define CREATE_ERR "An error occurred when trying to create an object"
# define TWICE_ERR "Twice single object detected, only one A, C, L object"

#endif