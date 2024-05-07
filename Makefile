# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/14 10:06:00 by lgosselk          #+#    #+#              #
#    Updated: 2024/05/07 11:31:24 by sbelomet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minirt

GCC			=	gcc
RM			=	rm -rf
HEADER		=	-I includes
LIBFT_PATH	=	./libft/libft.a
MLX_PATH	=	./minilibx/libmlx.a
GCCFLAGS	= 	-Wall -Wextra -Werror
MLXFLAGS	=	-Lminilibx -lmlx -framework OpenGL -framework AppKit

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
ERRORS_DIR		=	errors/
PARSING_DIR		=	parsing/
RAY_UTILS_DIR	=	ray_utils/
MATH_UTILS_DIR	=	math_utils/
AABB_UTILS_DIR	=	aabb_utils/
COLOR_UTILS_DIR	=	color_utils/
VEC3_UTILS_DIR	=	vector3_utils/
HITBL_UTILS_DIR	=	hittable_utils/
MATER_UTILS_DIR	=	material_utils/
INTRV_UTILS_DIR	=	intervals_utils/

# Files
F_ERRORS		=	errors
F_UTILS			=	cleaning hittables_utils parsing_utils parsing_utils2
F_INIT			=	base_init camera_init
F_PARSING		=	file_parse creating_objs creating_uniques
F_COLOR			=	color color_ops1
F_DRAW			=	draw
F_MATH_UTILS	=	rng angles swap
F_AABB_UTILS	=	aabb
F_VEC3_UTILS	=	vector3 vector3_ops1 vector3_ops2 vector3_rand vector3_comp
F_RAY_UTILS		=	ray
F_HITBL_UTILS	=	hittable
F_MATER_UITLS	=	scatter_funcs material mat_ray_mods
F_INTRV_UTILS	=	intervals intervals_ops

FILES		=	$(addprefix $(INIT_DIR), $(F_INIT)) \
				$(addprefix $(DRAW_DIR), $(F_DRAW)) \
				$(addprefix $(UTILS_DIR), $(F_UTILS)) \
				$(addprefix $(ERRORS_DIR), $(F_ERRORS)) \
				$(addprefix $(PARSING_DIR), $(F_PARSING)) \
				$(addprefix $(COLOR_UTILS_DIR), $(F_COLOR)) \
				$(addprefix $(RAY_UTILS_DIR), $(F_RAY_UTILS)) \
				$(addprefix $(MATH_UTILS_DIR), $(F_MATH_UTILS)) \
				$(addprefix $(AABB_UTILS_DIR), $(F_AABB_UTILS)) \
				$(addprefix $(VEC3_UTILS_DIR), $(F_VEC3_UTILS)) \
				$(addprefix $(INTRV_UTILS_DIR), $(F_INTRV_UTILS)) \
				$(addprefix $(HITBL_UTILS_DIR), $(F_HITBL_UTILS)) \
				$(addprefix $(MATER_UTILS_DIR), $(F_MATER_UITLS)) \

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
	@mkdir -p $(OBJS_DIR)$(ERRORS_DIR)
	@mkdir -p $(OBJS_DIR)$(PARSING_DIR)
	@mkdir -p $(OBJS_DIR)$(COLOR_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(DRAW_DIR)
	@mkdir -p $(OBJS_DIR)$(MATH_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(AABB_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(VEC3_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(RAY_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(INTRV_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(HITBL_UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(MATER_UTILS_DIR)

clean :
	@make clean -C ./libft
	@make clean -C ./minilibx
	@$(RM) $(OBJS_DIR)
	@echo "$(RED)All objects files been deleted!$(DEFAULT)"

fclean : clean
	@make fclean -C ./libft
	@make clean -C ./minilibx
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) removed!$(DEFAULT)"

re: fclean all

_libft :
	@make -C ./libft

_mlx :
	@make -C ./minilibx

lfclean : 
	@make fclean -C ./libft
	@$(RM) $(OBJS_DIR)
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) removed! (NOT THE MLX)$(DEFAULT)"

rl: lfclean _libft $(OBJS_DIR) $(NAME)

.PHONY:	all clean fclean re