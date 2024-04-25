# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 16:27:07 by lgosselk          #+#    #+#              #
#    Updated: 2024/04/24 15:53:47 by lgosselk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

GCC			=	gcc
AR			=	ar rc
RM			=	rm -rf
LIB			=	ranlib
HEAD		=	-I includes
CFLAGS		=	-Wall -Wextra -Werror

GNL_DIR		=	gnl/
OBJS_DIR	=	objs/
IS_DIR		=	ft_is/
MEM_DIR		=	ft_mem/
PUT_DIR		=	ft_put/
STR_DIR		=	ft_str/
ALLOC_DIR	=	ft_alloc/
UTILS_DIR	=	ft_utils/

F_GNL		=	get_next_line
F_ALLOC		=	ft_calloc ft_malloc
F_MEM		=	ft_memset ft_memchr ft_memcmp ft_memcpy ft_memmove
F_PUT		=	ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd
F_IS		=	ft_isalpha ft_isascii ft_isdigit ft_isprint ft_isalnum
F_UTILS		= 	ft_abs ft_atoi ft_bzero ft_itoa ft_split ft_tolower ft_toupper ft_split_alloc
F_STR		=	ft_strchr ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy \
				ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr \
				ft_equal_strs

FILES		=	$(addprefix $(IS_DIR), $(F_IS)) \
				$(addprefix $(GNL_DIR), $(F_GNL)) \
				$(addprefix $(MEM_DIR), $(F_MEM)) \
				$(addprefix $(PUT_DIR), $(F_PUT)) \
				$(addprefix $(STR_DIR), $(F_STR)) \
				$(addprefix $(ALLOC_DIR), $(F_ALLOC)) \
				$(addprefix $(UTILS_DIR), $(F_UTILS)) \

SRCS		=	$(addsuffix .c, $(FILES)) \

OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES))) \

all:		$(OBJS_DIR) $(NAME)

$(NAME):	$(OBJS)
			@$(AR) $(NAME) $(OBJS)
			@$(LIB) $(NAME)

$(OBJS_DIR)%.o: %.c
	@$(GCC) $(CFLAGS) $(HEADER) -o $@ -c $<

$(OBJS_DIR):
			@mkdir -p $(OBJS_DIR)
			@mkdir -p $(OBJS_DIR)$(IS_DIR)
			@mkdir -p $(OBJS_DIR)$(GNL_DIR)
			@mkdir -p $(OBJS_DIR)$(MEM_DIR)
			@mkdir -p $(OBJS_DIR)$(PUT_DIR)
			@mkdir -p $(OBJS_DIR)$(STR_DIR)
			@mkdir -p $(OBJS_DIR)$(ALLOC_DIR)
			@mkdir -p $(OBJS_DIR)$(UTILS_DIR)

clean:
		@$(RM) $(OBJS_DIR)

fclean:		clean
		@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
