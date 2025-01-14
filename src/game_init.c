/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:47:46 by dpetrukh          #+#    #+#             */
/*   Updated: 2025/01/14 20:03:12 by dpetrukh         ###   ########.fr       */
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

	y = 0;
	while (y < TEXTURE_SIZE)
	{
		x = 0;
		while (x < TEXTURE_SIZE)
		{
			img->pixels[y][x] = my_mlx_pixel_get(img, x, y);
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
	load_image(data->textures[WALL_][0].path,
		&data->textures[WALL_][0], data->mlx_ptr);
	load_image(data->textures[WALL_][1].path,
		&data->textures[WALL_][1], data->mlx_ptr);
	load_image(data->textures[WALL_][2].path,
		&data->textures[WALL_][2], data->mlx_ptr);
	load_image(data->textures[WALL_][3].path,
		&data->textures[WALL_][3], data->mlx_ptr);
	copy_static_array(&data->textures[WALL_][0]);
	copy_static_array(&data->textures[WALL_][1]);
	copy_static_array(&data->textures[WALL_][2]);
	copy_static_array(&data->textures[WALL_][3]);
}

void print_texture(unsigned texture[TEXTURE_SIZE][TEXTURE_SIZE]) {
	for (int y = 0; y < TEXTURE_SIZE; y++) {
		for (int x = 0; x < TEXTURE_SIZE; x++) {
			printf("%3d", texture[y][x]);  // Exibe cada valor da textura
		}
		printf("\n");  // Pula para a próxima linha após imprimir uma linha da textura
	}
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
	data->frame = &frame;
	init_image(data->frame);
	data->black_screen = &black_screen;
	init_image(data->black_screen);
	load_all_images(data);
	//print_texture(data->textures[WALL_].pixels);
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
