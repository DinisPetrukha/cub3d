/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:36:12 by sephilip          #+#    #+#             */
/*   Updated: 2025/03/05 14:37:51 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	return_wall_side(float pos_x, float angle)
{
	int	vertical_collision;

	vertical_collision = has_decimal(pos_x);
	if (vertical_collision && angle < M_PI)
		return (3);
	else if (vertical_collision && angle > M_PI)
		return (2);
	else if (!vertical_collision && (angle < M_PI / 2 || angle > 3 * M_PI / 2))
		return (1);
	return (0);
}

//TESTE DE DISTANCIA PARA RAIO VERTICAL
int	vertical_ray(float line[2], float interval, float angle, float crds[4])
{
	float	center[2];
	float	new_x;
	float	y;

	if (interval == 0)
		return (-1);
	center[0] = (data_()->player->x + (PLYRSIZE / 2));
	center[1] = (data_()->player->y + (PLYRSIZE / 2));
	if (interval > 0)
		new_x = ceilf(center[0] / BLOCK_SIZE) * BLOCK_SIZE;
	else
		new_x = floorf(center[0] / BLOCK_SIZE) * BLOCK_SIZE;
	while (1)
	{
		y = line[0] * new_x + line[1];
		if (y < 0 || y > ((data_()->matrix_height - 1) * BLOCK_SIZE)
			|| new_x < 0 || new_x > ((data_()->matrix_width - 1) * BLOCK_SIZE))
			return (-1);
		if (collision(new_x / BLOCK_SIZE, y / BLOCK_SIZE, angle, crds))
			break ;
		new_x += interval;
	}
	return (distance(center[0], center[1], new_x, y));
}

//TESTE DE DISTANCIA PARA RAIO HORIZONTAL
int	horizontal_ray(float line[2], float interval, float angle, float crds[4])
{
	float	center[2];
	float	x;
	float	new_y;

	if (interval == 0)
		return (-1);
	center[0] = (data_()->player->x + (PLYRSIZE / 2));
	center[1] = (data_()->player->y + (PLYRSIZE / 2));
	if (interval > 0)
		new_y = ceilf(center[1] / BLOCK_SIZE) * BLOCK_SIZE;
	else
		new_y = floorf(center[1] / BLOCK_SIZE) * BLOCK_SIZE;
	while (1)
	{
		x = (new_y - line[1]) / line[0];
		if (x < 0 || x > ((data_()->matrix_width) * BLOCK_SIZE)
			|| new_y < 0 || new_y > ((data_()->matrix_height - 1) * BLOCK_SIZE))
			return (-1);
		if (collision(x / BLOCK_SIZE, new_y / BLOCK_SIZE, angle, crds))
			break ;
		new_y += interval;
	}
	return (distance(center[0], center[1], x, new_y));
}

float	fire_rays(float angle, float inc[2], float center[2], float cls_crds[4])
{
	float	rays[2];
	float	line[2];
	float	coords_hor[4];
	float	coords_ver[4];

	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
		return (horizontal_ray((float []){0, 0}, inc[1], angle, cls_crds));
	line[0] = tan(angle);
	line[1] = center[1] - (line[0] * center[0]);
	rays[0] = horizontal_ray(line, inc[1], angle, coords_hor);
	rays[1] = vertical_ray(line, inc[0], angle, coords_ver);
	if ((rays[0] <= rays[1] && rays[0] != -1) || rays[1] == -1)
	{
		float_array_copy(cls_crds, coords_hor, 4);
		return (rays[0]);
	}
	float_array_copy(cls_crds, coords_ver, 4);
	return (rays[1]);
}

//DEVOLVE DISTANCIA DE UM RAIO
float	rainbow(t_player *player, float angle, float collision_cords[4])
{
	float	center[2];
	float	increment[2];

	center[0] = (player->x + (PLYRSIZE / 2));
	center[1] = (player->y + (PLYRSIZE / 2));
	if (sin(angle) > 0)
		increment[1] = BLOCK_SIZE;
	else if (sin(angle) < 0)
		increment[1] = -BLOCK_SIZE;
	else
		increment[1] = 0;
	if (cos(angle) > 0)
		increment[0] = BLOCK_SIZE;
	else if (cos(angle) < 0)
		increment[0] = -BLOCK_SIZE;
	else
		increment[0] = 0;
	return (fire_rays(angle, increment, center, collision_cords));
}
