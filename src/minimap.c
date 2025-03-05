/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:38:48 by sephilip          #+#    #+#             */
/*   Updated: 2025/03/05 15:34:57 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_line_at_angle(float angle, int color, int x, t_image *image)
{
	float	d;
	float	cls_crds[4];

	color += 1;
	d = rainbow(data_()->player, rs(data_()->player->orient + angle), cls_crds);
	d = fabs(d * cosf(angle));
	if ((int)d >= 0 && ((int)d <= FOV_DEEPNESS))
		draw_bar(0, (BLOCK_SIZE_3D / d) * ((WINDOW_WIDTH / 2) / tan(FOV / 2)), \
			x, cls_crds);
	else
		empty_bar(image, x);
}

//ALWAYS ODD NUMBERS OF NUM_RAYS
void	draw_rays_range(float mi, float ma, int rays, int color)
{
	float	angle_step;
	float	current_angle;
	int		i;

	rays += 1;
	angle_step = (ma - mi) / (NUM_RAYS);
	current_angle = mi;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		draw_line_at_angle(current_angle, color, i, data_()->frame);
		current_angle += angle_step;
		i += (WINDOW_WIDTH / NUM_RAYS);
	}
}

void	draw_line_map(t_player *player, float angle, int color, t_image *image)
{
	int	center[2];
	int	line[2];
	int	i;
	int	hit_wall_flag;

	center[0] = player->y + (PLYRSIZE / 2);
	center[1] = player->x + (PLYRSIZE / 2);
	i = 0;
	hit_wall_flag = 0;
	while (i < FOV_DEEPNESS && hit_wall_flag == 0)
	{
		line[0] = center[0] + i * sin(player->orient + angle);
		line[1] = center[1] + i * cos(player->orient + angle);
		if (verify_corner(line[1], line[0]))
			break ;
		if (!is_wall_line(data_(), line[0], line[1], &hit_wall_flag))
			my_mlx_pixel_put(image, line[0], line[1], color);
		i++;
	}
}

void	draw_player_rays(float angle_min, float angle_max, int nrays, int color)
{
	float	angle_step;
	float	current_angle;
	int		i;

	angle_step = (angle_max - angle_min) / (nrays - 1);
	current_angle = angle_min;
	i = 0;
	while (i < nrays)
	{
		draw_line_map(data_()->player, current_angle, color, data_()->frame);
		current_angle += angle_step;
		i++;
	}
}

void	draw_player(t_player *player)
{
	if (data_()->first_render == 0)
	{
		player->y = (player->y * BLOCK_SIZE);
		player->x = (player->x * BLOCK_SIZE);
		data_()->first_render = 1;
	}
	draw_square(player->x, player->y, 0x00FF0000, PLYRSIZE);
	draw_player_rays(-FOV_WIDE, FOV_WIDE, FOV_DEEPNESS, RAY);
}
