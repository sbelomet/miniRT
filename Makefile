# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/14 10:06:00 by lgosselk          #+#    #+#              #
#    Updated: 2024/06/11 14:00:49 by lgosselk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

GCC			=	gcc
RM			=	rm -rf
HEADER		=	-I includes
LIBFT_PATH	=	./libft/libft.a
MLX_PATH	=	./mlx/libmlx.a
GCCFLAGS	= 	-Wall -Wextra -Werror
MLXFLAGS	=	-Lmlx -lmlx -framework OpenGL -framework AppKit

DEFAULT	=	\033[0m
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m

# Directories
SRCS_DIR		=	src/
INIT_DIR		=	init/
OBJS_DIR		=	objs/
DRAW_DIR		=	draw/
UTILS_DIR		=	utils/
HOOKS_DIR		=	hooks/
ERRORS_DIR		=	errors/
PARSING_DIR		=	parsing/
RAY_UTILS_DIR	=	ray_utils/
MATH_UTILS_DIR	=	math_utils/
COLOR_UTILS_DIR	=	color_utils/
VEC3_UTILS_DIR	=	vector3_utils/
VEC4_UTILS_DIR	=	vector4_utils/
OBJ_UTILS_DIR	=	objects_utils/
MATER_UTILS_DIR	=	material_utils/
INTRV_UTILS_DIR	=	intervals_utils/
LIGHT_UTILS_DIR	=	light_utils/
GTFM_DIR		=	geometric_tfm/
MTRX_UTILS_DIR	=	matrices_utils/

# Files
F_ERRORS		=	errors
F_UTILS			=	cleaning parsing_utils parsing_utils2 parsing_utils3
F_INIT			=	base_init camera_utils
F_PARSING		=	file_parse creating_objs creating_uniques defaults
F_COLOR			=	color color_ops1
F_DRAW			=	draw
F_HOOKS			=	handle_hooks attribute_hook handle_hooks2 mouse_hook rotation_hook \
					rotation_hook2 translate_hook translate_hook2 translate_z_hook translate_z_hook2
F_MATH_UTILS	=	rng angles swap close_enough
F_VEC3_UTILS	=	vector3 vector3_ops1 vector3_ops2 vector3_rand vector3_comp vector3_ops3
F_VEC4_UTILS	=	vector4 vector4_ops
F_RAY_UTILS		=	ray
F_OBJ_UTILS		=	intersections_funcs obj_list_utils plane_inter sphere_inter cylinder_inter cone_inter cylinder_utils
F_MATER_UITLS	=	material mat_funcs
F_INTRV_UTILS	=	intervals intervals_ops
F_LIGHT_UTILS	=	light_funcs light_list_utils light_funcs2
F_GTFM			=	gtform gtfm_transforms gtform_ops gtfm_rotation
F_MTRX_UTILS	=	matrices matrices_ops matrices_inverse

FILES		=	$(addprefix $(INIT_DIR), $(F_INIT)) \
				$(addprefix $(ERRORS_DIR), $(F_ERRORS)) \
				$(addprefix $(PARSING_DIR), $(F_PARSING)) \
				$(addprefix $(UTILS_DIR), $(F_UTILS)) \
				$(addprefix $(HOOKS_DIR), $(F_HOOKS)) \
				$(addprefix $(DRAW_DIR), $(F_DRAW)) \
				$(addprefix $(COLOR_UTILS_DIR), $(F_COLOR)) \
				$(addprefix $(INTRV_UTILS_DIR), $(F_INTRV_UTILS)) \
				$(addprefix $(VEC3_UTILS_DIR), $(F_VEC3_UTILS)) \
				$(addprefix $(VEC4_UTILS_DIR), $(F_VEC4_UTILS)) \
				$(addprefix $(RAY_UTILS_DIR), $(F_RAY_UTILS)) \
				$(addprefix $(OBJ_UTILS_DIR), $(F_OBJ_UTILS)) \
				$(addprefix $(MATER_UTILS_DIR), $(F_MATER_UITLS)) \
				$(addprefix $(MATH_UTILS_DIR), $(F_MATH_UTILS)) \
				$(addprefix $(LIGHT_UTILS_DIR), $(F_LIGHT_UTILS)) \
				$(addprefix $(GTFM_DIR), $(F_GTFM)) \
				$(addprefix $(MTRX_UTILS_DIR), $(F_MTRX_UTILS)) \

SRCS		=	src/main.c \
				$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES))) \
				
				

OBJS		=	objs/main.o \
				$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES))) \

all : _libft _mlx $(OBJS_DIR) $(NAME)

$(NAME) : $(OBJS) $(LIBFT_PATH) $(MLX_PATH)
	@$(GCC) $(GCCFLAGS) $(OBJS) $(LIBFT_PATH) $(MLX_PATH) $(MLXFLAGS) -o $(NAME) 
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(GCC) $(GCCFLAGS) $(HEADER) -o $@ -c $<
	@echo "$(YELLOW)$< added to the oven!$(DEFAULT)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)$(UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(INIT_DIR)
	@mkdir -p $(OBJS_DIR)$(HOOKS_DIR)
	@mkdir -p $(OBJS_DIR)$(ERRORS_DIR)
	@mkdir -p $(OBJS_DIR)$(PARSING_DIR)
	@mkdir -p $(OBJS_DIR)$(COLOR_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(DRAW_DIR)
	@mkdir -p $(OBJS_DIR)$(MATH_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(VEC3_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(VEC4_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(RAY_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(INTRV_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(OBJ_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(MATER_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(LIGHT_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(GTFM_DIR)
	@mkdir -p $(OBJS_DIR)$(MTRX_UTILS_DIR)

clean :
	@make clean -C ./libft
	@make clean -C ./mlx
	@$(RM) $(OBJS_DIR)
	@echo "$(RED)All objects files been deleted!$(DEFAULT)"

fclean : clean
	@make fclean -C ./libft
	@make clean -C ./mlx
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) removed!$(DEFAULT)"

re: fclean all

_libft :
	@make -C ./libft

_mlx :
	@make -C ./mlx

lfclean : 
	@make fclean -C ./libft
	@$(RM) $(OBJS_DIR)
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) removed! (NOT THE MLX)$(DEFAULT)"

rl: lfclean _libft $(OBJS_DIR) $(NAME)

.PHONY:	all clean fclean re