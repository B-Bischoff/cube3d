# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbischof <bbischof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 11:20:06 by bbischof          #+#    #+#              #
#    Updated: 2022/04/27 16:19:40 by bbischof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OS = $(shell uname -s)
ifeq ($(OS), Darwin)
	END=$'\x1b[0m
	RED=$'\x1b[31m
	GREEN=$'\x1b[32m
	BLUE=$'\x1b[34m
	ERASE=\033[2K\r
else
	END=$'\033b[0m
	RED=$'\033[31m
	GREEN=$'\033[32m
	BLUE=$'\033[34m
	ERASE=$'\033b[2K\r
endif

VPATH = ./:\
		get_next_line:/\
		math:/\
		color:/\
		strings:/\
		memory:/\
		lists:/\

# Memory
SRCS += ft_bzero.c ft_calloc.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c ft_memcmp.c

# Strings
SRCS +=	ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_empty_str.c

# Lists
SRCS += ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

# Get next line
SRCS += get_next_line.c get_next_line_utils.c

# Math
SRCS += ft_abs.c ft_clamp.c ft_create_vector.c ft_get_angle.c ft_lerp.c ft_rad_deg.c ft_set_vector.c ft_vector_convert.c ft_vector_length.c ft_vector_lerp.c ft_vector_rot.c

# Color
SRCS += ft_color_lerp.c ft_get_color.c ft_create_color.c

OBJS = ${addprefix .objects/, ${SRCS:.c=.o}}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

HEADER = libft.h

CC = gcc

RM = rm -f

FLAGS = -Wall -Werror -Wextra

.objects/%.o : %.c ${HEADER}
	@mkdir -p .objects
	@${CC} ${FLAGS} -c $< -o $@
	@printf "$(ERASE)$(BLUE)[BUILDING]$(END) $@"

$(NAME): ${OBJS}
	ar rcs ${NAME} ${OBJS}
	@printf "$(ERASE)$(GREEN)[CREATED $(NAME)]$(END)\n"

all: ${NAME}

clean:
	${RM} ${OBJS} ${OBJS_BONUS}
	@echo "$(RED)[DELETED LIBFT OBJS]$(END)"

fclean: clean
	${RM} ${NAME}
	@echo "$(RED)[DELETED]$(END) $(NAME)"

re: fclean all

.PHONY: all clean fclean re bonus

.SILENT: all fclean clean re $(NAME) .objects/*.o 