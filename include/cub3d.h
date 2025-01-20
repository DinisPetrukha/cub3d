#ifndef CUB3_H
# define CUB3_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

# define WINDOW_HEIGHT	1000
# define WINDOW_WIDTH	1000
# define BLOCK_SIZE 32
# define PLAYER_SIZE_V1 BLOCK_SIZE * 0.375
# define FOV_WIDE 0.5
//FOV CANT BE MULTIPLE OF PI. OR DISTANCE_TO_SCREEN WILL EXPLODE
# define FOV 1.0472 // 60 degrees in raians
# define FOV_DEEPNESS 300

# define PLAYER_SPEED 0.5
# define ROTATION_SPEED 0.007

# define NUMBER_OF_TEXTURES 1
# define TEXTURE_SIZE 64

# define BLOCK_SIZE_3D 64.0f
# define DISTANCE_TO_SCREEN (WINDOW_WIDTH / 2) / tan(FOV / 2)
//# define MAX_BAR_HEIGHT 900

#define NUM_RAYS 100

# define W 119
# define UP 65362
# define S 115
# define DOWN 65364
# define A 97
# define LEFT 65361
# define D 100
# define RIGHT 65363

# define ESC 65307
# define Q 113

# include <math.h>
# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>
# include <time.h>

typedef unsigned char byte;

typedef enum e_type
{
	WALL_,
}	t_type;


typedef struct s_image
{
	void			*img_ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
	char			*path;
	unsigned int	pixels[TEXTURE_SIZE][TEXTURE_SIZE];
}	t_image;

typedef struct s_binds
{
	int	move_up;
	int	move_down;
	int	move_left;
	int	move_right;
	int	camera_left;
	int	camera_right;
	int	esc;
}	t_binds;

typedef struct s_player {
	float	x;
	float	y;
	float	orient;
	char	angle_pos;
}
	t_player;

typedef struct s_data {
	void		*mlx_ptr;
	void		*window;
	//void		*image_ptr;
	char		**map;
	int			first_render;
	int			matrix_width;
	int			matrix_height;
	int			dif_timer;
	int			ceiling_texture;
	int			floor_texture;
//	char		*textures; [0] = N [1] = E [2] = S [3] = W
	t_binds		*key;
	t_image		textures[NUMBER_OF_TEXTURES][4];
	t_image		*frame;
	t_image		*black_screen;
	t_player	*player;
}
	t_data;

// MY_FT_STRJOIN
char	*my_ft_strjoin(char const *s1, char const *s2);

// OPEN_FILE
//int		open_file(char *path);
//char	**read_map(int fd);
void	free_mat(char **mat);
void	input_file(t_data *data, char *file);
void	map_dimensions(t_data *data, int fd);
void	name_check(char *name);
void	init_map(t_data *data, char *file, int start_map);
void	map_constructor(char *file);

//FUNCTIONS_UTILS
void	init_keys(t_data *data);
void	init_image(t_image *image);

// DATA_UTILS
t_data	*data_(void);
void	print_map(void);

//GAME_INIT
int		game_init(void);
void	init_data(t_data *data);
void	load_sructures(t_data *data);

//CLOSE_FREE
int		close_window(t_data *data);

//PLAYER_MOVEMENT
int		is_wall_player(t_data *data, float next_y, float next_x);
int		is_wall_line(t_data *data, float next_y, float next_x, int *flag);
void	player_movement(int keycode, t_data *data);
// int		keypress(int keycode, t_data *data);
int		key_lift(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
void	apply_changes(t_data *data);
void	player_input(t_binds *key, int keycode, bool pressed);

//DRAW_MAP

void	draw_half(t_image *image, int ccolor, int fcolor);
void	empty_bar(t_image *image, int pos_x);
void	draw_bar(t_image *image, float distant, int pos_x, int color, float collision_cords[4]);

int		loop_handler(void *param);
void	draw_rays_range(t_player *player, float angle_min, float angle_max, int num_rays, int color, t_image *image);
//void	draw_player_lines(t_player *player, int color, t_image *image);
void	draw_square_to_image(int x, int y, int color, int size, t_image *image);
void	draw_player(t_player *player);
void	my_mlx_pixel_put(t_image *image, int y, int x, int color);
unsigned int	my_mlx_pixel_get(t_image *data, int x, int y);


//IS_VALID
void	exitmap(char **map, int ret, char *msg);
void	free_map(char **map, int ret);
int	is_protected(char **map, int j, int i);
void	optimise_map(t_data *data, char **map);
void	check_symbols(char **map);
void	check_player(char **map, t_player *player);

#endif
