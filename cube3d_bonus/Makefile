END=$'\x1b[0m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
BLUE=$'\x1b[34m
ERASE=\033[2K\r

VPATH = sources/:\
		sources/draw/:\
		sources/grid/:\
		sources/mlx_utils/:\
		sources/utils/:\
		sources/rays/:\
		sources/parsing/\


# Draw
SRCS += bresenham.c \
		draw.c \
		circle.c \
		square.c \

# Grid
SRCS +=	init_grid.c \
		print_grid.c \
		set_grid_cell.c \

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

# Rays
SRCS += create_rays.c \
		dda.c \
		calculate_collisions.c \
		rays_render.c \
		perp_wall_dist.c \

# Parsing
SRCS += parsing.c \
		map_check.c \
		description_check.c \
		print_map.c \

MAIN = main.c
MAIN_BONUS = main_bonus.c

OBJS = $(addprefix .objects/, $(SRCS:.c=.o))
MAIN_OBJ = $(addprefix .objects/, $(MAIN:.c=.o))
MAIN_BONUS_OBJ = $(addprefix .objects/, $(MAIN_BONUS:.c=.o))

INCLUDES = includes/cube3d.h \
			includes/alias.h


CC = gcc

CFLAGS = -Wall -Wextra -Werror

DEBUG_FLAGS = #-fsanitize=address -g3

OPTI_FLAGS = #-O3

NAME = cube_3d

NAME_BONUS = cube_3d_bonus

LIB = libft/libft.a

LFT = -L libft -lft

RM = rm -rf

all: mlx_lib lib $(NAME)

bonus: mlx_lib lib $(NAME_BONUS)

mlx_lib:
	make -C mlx

lib:
	make -C libft

$(NAME): $(OBJS) $(MAIN_OBJ) $(INCLUDES) $(LIB) Makefile
	@$(CC) $(OBJS) $(MAIN_OBJ) ${CFLAGS} $(DEBUG_FLAGS) $(OPTI_FLAGS) -Lmlx -lmlx -framework OpenGL -framework Appkit $(LFT) -I includes -o $@
	@echo "$(ERASE)$(GREEN)[CREATED $(NAME)]$(END)"

$(NAME_BONUS): $(OBJS) $(MAIN_BONUS_OBJ) $(INCLUDES) $(LIB) Makefile
	@$(CC) $(OBJS) $(MAIN_BONUS_OBJ) ${CFLAGS} $(DEBUG_FLAGS) $(OPTI_FLAGS) -Lmlx -lmlx -framework OpenGL -framework Appkit $(LFT) -I includes -o $@
	@echo "$(ERASE)$(GREEN)[CREATED $(NAME)]$(END)"
.objects/%.o:	%.c Makefile $(INCLUDES)
	@mkdir -p .objects
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTI_FLAGS) -Imlx -I includes -c $< -o $@
	@printf "$(ERASE)$(BLUE)[BUILDING]$(END) $@"

clean:
	@${RM} ${OBJS} ${MAIN_OBJ} ${MAIN_BONUS_OBJ} 
	@make fclean -C libft
	@echo "${RED}[DELETED CUBE3D OBJS]${END}"

fclean:         clean
	@${RM} ${NAME} ${NAME_BONUS}
	@${RM} .objects
	@echo "${RED}[DELETED]${END} ${NAME}"

re:	fclean all
