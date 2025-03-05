/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:20:57 by sephilip          #+#    #+#             */
/*   Updated: 2025/03/05 15:41:41 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define RED   "\x1B[31m"
# define RESET "\x1B[0m"
# define WALL 0xFFFFFF
# define FLOOR 0xB09F9E
# define RAY	0xE7E7E7

# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080
# define BLOCK_SIZE 16
//PLYRSIZE = BLOCK_SIZE * 0.375
# define PLYRSIZE 6
# define FOV_WIDE 0.5
# define FOV 1.0472
# define FOV_DEEPNESS 300

# define PLAYER_SPEED 0.5
# define ROTATION_SPEED 0.007

# define NUMBER_OF_TEXTURES 1
# define TEXTURE_SIZE 64

//BLOCK_SIZE = (float)(BLOCK_SIZE * 2)
# define BLOCK_SIZE_3D 32.0f
//DISTANCE_TO_SCREEN = (WINDOW_WIDTH / 2) / TAN(FOV / 2)
//# define DISTANCE_TO_SCREEN (1920 / 2) / tan(1.0472 / 2)

//NUM_RAYS = WINDOW_WIDTH
# define NUM_RAYS 1920

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
# include <sys/time.h>

typedef unsigned char	t_byte;

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

typedef struct s_player
{
	float	x;
	float	y;
	float	orient;
	char	angle_pos;
}	t_player;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*window;
	char		**map;
	int			first_render;
	int			matrix_width;
	int			matrix_height;
	int			dif_timer;
	int			cel_tex;
	int			floor_texture;
	t_binds		*key;
	t_image		textures[NUMBER_OF_TEXTURES][4];
	t_image		*frame;
	t_player	*player;
}	t_data;

//AUX.C
void			my_mlx_pixel_put(t_image *image, int y, int x, int color);
unsigned int	my_mlx_pixel_get(t_image *data, int x, int y);
int				has_decimal(float num);
int				float_equal(float a, float b);
float			distance(float x1, float y1, float x2, float y2);

//CLOSE_FREE.C
void			clean_textures(t_data *data);
int				close_window(t_data *data);
int				error_return(char *str, int value);
void			exit_error(char *str, int exit_int);
void			write_close_window(char *str);

//DATA_UTILS.C
t_data			*data_(void);
void			print_map(void);

//DRAW_MAP.C
void			empty_bar(t_image *image, int pos_x);
void			draw_bar(int c, float bar_size, int p, float cc[4]);
void			draw_square(int x, int y, int color, int size);
void			draw_minimap(t_data *data);
int				loop_handler(void *param);

//FUNCTIONS_UTILS.C
void			init_image(t_image *image);
void			init_keys(t_data *data);

//GAME_INIT.C
void			init_data(t_data *data);
void			copy_static_array(t_image *img);
void			load_image(char *path, t_image *img, void *mlx_ptr);
void			load_all_images(t_data *data);
int				game_init(void);

//HELPER.C
int				ft_isspace(int c);
void			exitmap(char **map, int ret, char *msg);
void			free_map(char **map);
int				only_spaces(char *line);

//IF_VALID.C
int				is_protected(char **map, int j, int i);
void			optimise_map(t_data *data, char **map);
void			check_symbols(char **map);
void			player_orient_reading(int j, int i, t_player *p, char **map);
void			check_player(char **map, t_player *player);

//KEYBOARD_APPLY.C
void			move_up(t_data *data, t_player *p, float pos_y, float pos_x);
void			move_down(t_data *data, t_player *p, float pos_y, float pos_x);
void			move_left(t_data *data, t_player *p, float s_y, float s_x);
void			move_right(t_data *data, t_player *p, float s_y, float s_x);
void			apply_changes(t_data *data);

//KEYBOARD.C
void			player_input(t_binds *key, int keycode, bool pressed);
int				key_lift(int keycode, t_data *data);
int				key_press(int keycode, t_data *data);

//MAP_CONSTRUCTOR.C
void			map_copy(char *line, int fd, t_data *data, int i);
void			init_map(t_data *data, char *file, int start_map);
void			map_constructor(char *file);
void			map_height_count(char *line, int *start_map, int line_nbr);
int				read_file(char *line, int step, int *start_map, int line_nbr);

//MINIMAP.C
void			draw_line_at_angle(float angle, int col, int x, t_image *image);
void			draw_rays_range(float mi, float ma, int rays, int col);
void			draw_line_map(t_player *p, float a, int col, t_image *i);
void			draw_player_rays(float a_min, float a_max, int nrays, int col);
void			draw_player(t_player *player);

//MY_FT_STRJOIN.C
size_t			my_ft_strlen(const char	*str);
char			*my_ft_strjoin(char const *s1, char const *s2);

//OPEN_FILE.C
void			free_mat(char **mat);
int				encode_rgb(t_byte red, t_byte green, t_byte blue);
int				apply_colors(t_data *data, int colors[3], int value);
void			input_file(t_data *data, char *file, int line_nbr, int step);
void			name_check(char *name);

//PHYSICS.C
int				collision(float p_x, float p_y, float angle, float c_arr[4]);
void			float_array_copy(float *dst, float *src, int len);
float			rs(float angle);
bool			verify_corner(int x, int y);
float			wall_x(float collision_cords[4]);

//PLAYER_MOVEMENT.C
int				is_wall_line(t_data *data, float n_y, float n_x, int *flag);
int				is_wall_player(t_data *data, float next_y, float next_x);
void			camera_left(t_data *data, t_player *player);
void			camera_right(t_data *data, t_player *player);

//RAYS.C
int				return_wall_side(float pos_x, float angle);
int				vertical_ray(float line[2], float i, float a, float crds[4]);
int				horizontal_ray(float line[2], float i, float a, float crds[4]);
float			fire_rays(float a, float inc[2], float c[2], float cls_crds[4]);
float			rainbow(t_player *p, float a, float collision_cords[4]);

//TEXTURE_CREATOR.C
int				add_color(int i, int j, char *line, int colors[4]);
int				ft_coloratoi(const char *nptr, int res, int separator);
int				add_texture(char *line, char **mem, int value);

#endif
