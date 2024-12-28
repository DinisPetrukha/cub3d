/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:47:46 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/12/28 19:24:13 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data)
{
	static t_player	player;

	data->player = &player;
	check_player(data->map, data->player);
}

void	copy_static_array(t_image *img)
{
	int	x;
	int	y;
	int	pixel_offset;

	y = 0;
	while (y < TEXTURE_SIZE)
	{
		while (x < TEXTURE_SIZE)
		{
			pixel_offset = y * img->line_len + x * (img->bpp / 8);
			img->pixels[y][x] = *(int *)(img->addr + pixel_offset);
			x++;
		}
		y++;
	}
}

void	load_image(char *path, t_image *img, void *mlx_ptr)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path,
			&img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
}

void	load_all_images(t_data *data)
{
	load_image("texture/red_brick.xpm",
		&data->textures[WALL_], data->mlx_ptr);
}

// Retun 1 if success
// Return 0 if not success
int	game_init(void)
{
	t_data			*data;
	static t_image	frame;
	static t_image	black_screen;

	data = data_();
	data->dif_timer = 0;
	// Initializing The Mlx
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->window = mlx_new_window(data->mlx_ptr, WINDOW_HEIGHT, WINDOW_WIDTH, "cub3d");
	if (!data->window)
		return (0);
	// Initializing The Main Frame
	printf("Map Height: %i\nMap Width: %i\n", data->matrix_height, data->matrix_width);
	data->frame = &frame;
	init_image(data->frame);
	data->black_screen = &black_screen;
	init_image(data->black_screen);
	load_all_images(data);
	init_keys(data);
	// Close window when X it's Clicked
	mlx_hook(data->window, DestroyNotify, StructureNotifyMask,
		close_window, data);
	// Loop The Game
	mlx_hook(data->window, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, key_lift, data);
	mlx_loop_hook(data->mlx_ptr, loop_handler, data);
	mlx_loop(data->mlx_ptr);
	return (1);
}
