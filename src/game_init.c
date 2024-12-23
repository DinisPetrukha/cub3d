/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:47:46 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/29 16:49:27 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exitmap(data_()->map, 1, "Error\nMalloc\n");
	check_player(data->map, data->player);
}

// Retun 1 if success
// Return 0 if not success
int	game_init(void)
{
	t_data	*data;

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
	data->frame = malloc(sizeof(t_image));
	init_image(data->frame);
	init_keys(data);
	// Drawing Like a Picasso
	// loop_handler(data);
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