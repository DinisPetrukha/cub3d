/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:21:53 by sephilip          #+#    #+#             */
/*   Updated: 2025/03/05 14:22:54 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
