NAME = cub3d
SRC = src/my_ft_strjoin.c src/main.c src/data_utils.c src/open_file.c src/game_init.c src/functions_utils.c \
		src/draw_map.c src/close_free.c src/player_movement.c src/if_valid.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I include/
LIBFT = include/libft/libft.a
LIBFT_LIB = include/libft

MLX_LIB_DIR = include/mlx_linux/
MLX_INCLUDE = -I $(MLX_LIB_DIR)
MLX_FLAGS = -L$(MLX_LIB_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

all: $(LIBFT) $(OBJ) $(NAME)

$(LIBFT):
	@echo "\n-Compiling Libft...\n"
	@$(MAKE) -C $(LIBFT_LIB)

$(OBJ): %.o: %.c
	@echo "Compiling $@..."
	@$(MAKE) -s -C $(MLX_LIB_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
	@echo "\n-Linking $(NAME) with Libft and MLX...\n"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "\n--------------------------------"
	@echo "$(NAME) is ready!"
	@echo "--------------------------------"

clean:
	@echo "\n-Cleaning Libft..."
	$(MAKE) -C $(LIBFT_LIB) clean
	@echo "\n-Cleaning object files..."
	@rm -f $(OBJ)
	@echo "\n--------------------------------"
	@echo "$(NAME) object files cleaned!"
	@echo "--------------------------------"

fclean: clean
	@echo "\n-Cleaning $(NAME) and Libft..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_LIB) fclean
	@echo "\n--------------------------------"
	@echo "$(NAME) cleaned!"
	@echo "--------------------------------"

re: fclean all

1:
	@make && ./$(NAME) map.cub

2:
	@make && ./$(NAME) map2.cub

.PHONY: all clean fclean re
