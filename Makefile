NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

SRC = src/main.c \
	src/error_exit/exit.c \
	src/init/init_data_structures.c \
	src/init/init_textures.c \
	src/init/init.c \
	src/keypress/keypress.c \
	src/movement/cursor.c \
	src/movement/move.c \
	src/movement/rotate.c \
	src/parsing/map_create.c \
	src/parsing/map_name.c \
	src/parsing/map_open.c \
	src/parsing/map_valid.c \
	src/parsing/parser_fd.c \
	src/parsing/parser_utils.c \
	src/raycast/raycast_utils.c \
	src/raycast/raycast.c \
	src/utils/utils.c \
	src/utils/utils2.c

OBJ_DIR = objects
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

INC = -I includes/ -I includes/libft/ -I includes/minilibx-linux/

LIBFT_PATH = includes/libft/
MLX_PATH = includes/minilibx-linux/
MLX = $(MLX_PATH)libmlx_Linux.a

all: $(NAME)

# Compile objects
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ > /dev/null 2>&1


# Link program
$(NAME): $(OBJS)
	@make -sC $(LIBFT_PATH) > /dev/null 2>&1
	@echo "\033[1m\033[96mLIBFT\033[0m     [\033[92mcompiled\033[0m]"
	@chmod +x $(MLX_PATH)configure || true
	@make -sC $(MLX_PATH) > /dev/null 2>&1
	@echo "\033[1m\033[96mMLX\033[0m       [\033[92mcompiled\033[0m]"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -L$(LIBFT_PATH) -lft > /dev/null 2>&1
	@echo "\033[1m\033[96mCUB3D\033[0m     [\033[92mbuilt\033[0m]"


# Clean objects
clean:
	@rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_PATH) clean
	@make -sC $(MLX_PATH) clean

# Full clean
fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_PATH) fclean

# Rebuild
re: fclean all

.PHONY: all clean fclean re
