NAME = cub3d
SRC = src/aux.c src/close_free.c src/data_utils.c src/draw_map.c src/functions_utils.c src/game_init.c src/helper.c \
		src/if_valid.c src/keyboard_apply.c src/keyboard.c src/main.c src/map_constructor.c src/minimap.c \
		src/my_ft_strjoin.c src/open_file.c src/physics.c src/player_movement.c src/rays.c src/texture_creator.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
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
	@make && ./$(NAME) map/map.cub

2:
	@make && ./$(NAME) map/map2.cub

4:
	@make && ./$(NAME) map/map4.cub

.PHONY: all clean fclean re
