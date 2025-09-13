NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

SRC = src/main.c \
	src/parsing/check_map.c \
	src/parsing/create_map.c \
	src/parsing/parse_fd.c \
	src/init/init.c \
	src/init/init_textures.c \
	src/init/init_data_structures.c \
	src/raycast/raycast.c \
	src/error_exit/exit.c \
	src/utils.c

OBJ_DIR = objects
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

INC = -I includes/ -I includes/libft/ -I includes/minilibx-linux/

LIBFT_PATH = includes/libft/
MLX_PATH = includes/minilibx-linux/
MLX = $(MLX_PATH)libmlx_Linux.a

all: $(NAME)

# Compile objects and create directories automatically
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Link program
$(NAME): $(OBJS)
	@make -sC $(LIBFT_PATH) > /dev/null 2>&1
	@chmod +x $(MLX_PATH)configure || true
	@make -sC $(MLX_PATH) > /dev/null 2>&1
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -L$(LIBFT_PATH) -lft

# Clean objects
clean:
	rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_PATH) clean
	@make -sC $(MLX_PATH) clean

# Full clean
fclean: clean
	rm -f $(NAME)
	@make -sC $(LIBFT_PATH) fclean

# Rebuild
re: fclean all

.PHONY: all clean fclean re
