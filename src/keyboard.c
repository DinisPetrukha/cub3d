/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:20:16 by sephilip          #+#    #+#             */
/*   Updated: 2025/03/05 15:01:53 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	player_input(t_binds *key, int keycode, bool pressed)
{
	if (keycode == S)
		key->move_up = pressed;
	if (keycode == W)
		key->move_down = pressed;
	if (keycode == A)
		key->move_left = pressed;
	if (keycode == D)
		key->move_right = pressed;
	if (keycode == 65361)
		key->camera_left = pressed;
	if (keycode == 65363)
		key->camera_right = pressed;
	if (keycode == 65307)
		close_window(data_());
}

int	key_lift(int keycode, t_data *data)
{
	player_input(data->key, keycode, false);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	player_input(data->key, keycode, true);
	return (0);
}
