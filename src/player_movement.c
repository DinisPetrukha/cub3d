/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:00:40 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/21 20:00:40 by dpetrukh         ###   ########.fr       */
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

int	is_wall_line(t_data *data, float next_y, float next_x, int *flag)
{
	int	y;
	int	x;

	y = (int) next_y / BLOCK_SIZE;
	x = (int) next_x / BLOCK_SIZE;
	if (y >= data->matrix_height || x >= data->matrix_width)
		return (1);
	if (data->map[y][x] == '1')
	{
		*flag = 1;
		return (1);
	}
	return (0);
}

int	is_wall_player(t_data *data, float next_y, float next_x)
{
	int	top_left[2];
	int	top_right[2];
	int	bottom_right[2];
	int	bottom_left[2];

	top_left[0] = (int)(next_y / BLOCK_SIZE);
	top_left[1] = (int)(next_x / BLOCK_SIZE);
	top_right[0] = (int)(next_y / BLOCK_SIZE);
	top_right[1] = (int)((next_x + PLYRSIZE) / BLOCK_SIZE);
	bottom_right[0] = (int)((next_y + PLYRSIZE) / BLOCK_SIZE);
	bottom_right[1] = (int)((next_x + PLYRSIZE) / BLOCK_SIZE);
	bottom_left[0] = (int)((next_y + PLYRSIZE) / BLOCK_SIZE);
	bottom_left[1] = (int)(next_x / BLOCK_SIZE);
	if (data->map[top_left[0]][top_left[1]] == '1' ||
		data->map[top_right[0]][top_right[1]] == '1' ||
		data->map[bottom_right[0]][bottom_right[1]] == '1' ||
		data->map[bottom_left[0]][bottom_left[1]] == '1')
		return (1);
	return (0);
}

void	move_up(t_data *data, t_player *player, float pos_y, float pos_x)
{
	if (data->key->move_down)
	{
		if (!is_wall_player(data, player->y + pos_y, player->x))
			player->y += pos_y;
		if (!is_wall_player(data, player->y, player->x + pos_x))
			player->x += pos_x;
	}
}

void	move_down(t_data *data, t_player *player, float pos_y, float pos_x)
{
	if (data->key->move_up)
	{
		if (!is_wall_player(data, player->y - pos_y, player->x))
			player->y -= pos_y;
		if (!is_wall_player(data, player->y, player->x - pos_x))
			player->x -= pos_x;
	}
}

//strafe_y, strafe_x
void	move_left(t_data *data, t_player *player, float s_y, float s_x)
{
	if (data->key->move_left)
	{
		if (!is_wall_player(data, player->y - s_y, player->x))
			player->y -= s_y;
		if (!is_wall_player(data, player->y, player->x - s_x))
			player->x -= s_x;
	}
}

//strafe_y, strafe_x
void	move_right(t_data *data, t_player *player, float s_y, float s_x)
{
	if (data->key->move_right)
	{
		if (!is_wall_player(data, player->y + s_y, player->x))
			player->y += s_y;
		if (!is_wall_player(data, player->y, player->x + s_x))
			player->x += s_x;
	}
}

void	camera_left(t_data *data, t_player *player)
{
	if (data->key->camera_left)
	{
		player->orient -= ROTATION_SPEED;
		if (player->orient < 0)
			player->orient += 2 * M_PI;
	}
}

void	camera_right(t_data *data, t_player *player)
{
	if (data->key->camera_right)
	{
		player->orient += ROTATION_SPEED;
		if (player->orient >= 2 * M_PI)
			player->orient -= 2 * M_PI;
	}
}

void	apply_changes(t_data *data)
{
	float	pos_y;
	float	pos_x;
	float	strafe_y;
	float	strafe_x;

	pos_y = (PLAYER_SPEED * sin(data->player->orient));
	pos_x = (PLAYER_SPEED * cos(data->player->orient));
	strafe_y = (PLAYER_SPEED * cos(data->player->orient));
	strafe_x = -(PLAYER_SPEED * sin(data->player->orient));
	move_up(data, data->player, pos_y, pos_x);
	move_down(data, data->player, pos_y, pos_x);
	move_right(data, data->player, strafe_y, strafe_x);
	move_left(data, data->player, strafe_y, strafe_x);
	camera_left(data, data->player);
	camera_right(data, data->player);
}