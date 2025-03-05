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
