VPATH = sources/:\
		sources/draw/:\
		sources/grid/:\
		sources/mlx_utils/:\
		sources/utils/:\
		sources/rays/:\
		sources/parsing/:\
		sources/textures/\


SRCS = main.c 

# Draw
SRCS += bresenham.c \
		draw.c \
		circle.c \
		square.c \
		triangle.c \

# Grid
SRCS +=	print_grid.c \
		set_grid_cell.c \
		grid_utils.c \

# Mlx utils
SRCS +=	hooks.c \
		mlx_utils.c \
		update.c \

# Utils
SRCS += fps_counter.c \
		init_vision.c \
		floor_and_ceiling.c \
		return_error.c \
		minimap.c \
		player_movement.c \
		free_cube.c \

# Rays
SRCS += create_rays.c \
		dda.c \
		calculate_collisions.c \
		rays_render.c \

# Parsing
SRCS += parsing.c \
		map_check.c \
		description_check.c \
		print_map.c \
		get_map.c \

# Textures
SRCS += init_textures.c \
		render_sprite.c \
		sprites_init.c \
		get_text_pixel.c \

OBJS = $(addprefix .objects/, $(SRCS:.c=.o))

INCLUDES = includes/cube3d.h \
			includes/alias.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

DEBUG_FLAGS = #-fsanitize=address -g3

OPTI_FLAGS = -O3

NAME = cube_3d

LIB = Libft/libft.a

LFT = -L Libft -lft

RM = rm -rf

OS = $(shell uname -s)

ifeq ($(OS), Darwin)
	OS_VAL = 1
	MLX = ../mlx_mac
	MLX_FLAGS = -L${MLX} -lmlx -framework OpenGL -framework Appkit $(LFT)
	END=$'\x1b[0m
	RED=$'\x1b[31m
	GREEN=$'\x1b[32m
	BLUE=$'\x1b[34m
	ERASE=\033[2K\r
else
	OS_VAL = 2
	MLX = ../mlx_linux
	MLX_FLAGS = -L${MLX} -lmlx -lXext -lX11 -lm -lz $(LFT)
	END=\033[0m
	RED=\033[31m
	GREEN=\033[32m
	BLUE=\033[34m
	ERASE=\033[2K\r
endif

all: mlx_lib lib $(NAME)

bonus: mlx_lib lib $(NAME_BONUS)

mlx_lib:
	make -C ${MLX}

lib:
	make -C Libft

$(NAME): $(OBJS) $(INCLUDES) $(LIB) Makefile
	@$(CC) $(OBJS) ${CFLAGS} $(DEBUG_FLAGS) $(OPTI_FLAGS) $(MLX_FLAGS) -I includes -o $@
	@echo "$(ERASE)$(GREEN)[CREATED $(NAME)]$(END)"

.objects/%.o:	%.c Makefile $(INCLUDES)
	@mkdir -p .objects
	@$(CC) -D OS=$(OS_VAL) $(CFLAGS) $(DEBUG_FLAGS) $(OPTI_FLAGS) -I${MLX} -I includes -c $< -o $@
	@printf "$(ERASE)$(BLUE)[BUILDING]$(END) $@"

clean:
	@${RM} ${OBJS} ${MAIN_OBJ} ${MAIN_BONUS_OBJ} 
	@make fclean -C Libft
	@echo "${RED}[DELETED CUBE3D OBJS]${END}"

fclean:	clean
	@${RM} ${NAME} ${NAME_BONUS}
	@${RM} .objects
	@echo "${RED}[DELETED]${END} ${NAME}"

re:	fclean all
