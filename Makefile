# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/14 10:06:00 by lgosselk          #+#    #+#              #
#    Updated: 2024/04/19 15:22:23 by sbelomet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minirt

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
SRCS_DIR	=	src/
OBJS_DIR	=	objs/
ERRORS_DIR	=	errors/
COLOR_DIR	=	color/
DRAW_DIR	=	draw/

# Files
F_ERRORS	=	errors
F_COLOR		=	color
F_DRAW		=	draw

FILES		=	$(addprefix $(ERRORS_DIR), $(F_ERRORS)) \
				$(addprefix $(COLOR_DIR), $(F_COLOR)) \
				$(addprefix $(DRAW_DIR), $(F_DRAW)) \

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
	@mkdir -p $(OBJS_DIR)$(ERRORS_DIR)
	@mkdir -p $(OBJS_DIR)$(COLOR_DIR)
	@mkdir -p $(OBJS_DIR)$(DRAW_DIR)

clean :
	@make clean -C ./libft
	@make clean -C ./minilibx
	@$(RM) $(OBJS_DIR)
	@echo "$(RED)All objects files been deleted!$(DEFAULT)"

fclean : clean
	@make fclean -C ./libft
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) removed!$(DEFAULT)"

re: fclean all

_libft :
	@make -C ./libft

_mlx :
	@make -C ./minilibx

.PHONY:	all clean fclean re