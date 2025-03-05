/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:03:53 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/21 20:03:53 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	empty_bar(t_image *image, int pos_x)
{
	int	pos_y;

	pos_y = 0;
	while (pos_y < WINDOW_HEIGHT / 2)
	{
		my_mlx_pixel_put(image, pos_y, pos_x, data_()->cel_tex);
		pos_y++;
	}
	while (pos_y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(image, pos_y, pos_x, data_()->floor_texture);
		pos_y++;
	}
}

void	draw_bar(int c, float bar_size, int p, float cc[4])
{
	int		start_y;
	int		end_y;
	int		t[2];

	start_y = (WINDOW_HEIGHT / 2) - ((int)bar_size / 2);
	end_y = (WINDOW_HEIGHT / 2) + ((int)bar_size / 2);
	t[0] = (int)(wall_x(cc) * TEXTURE_SIZE) % TEXTURE_SIZE;
	while (c < WINDOW_HEIGHT)
	{
		if (c >= start_y && c < end_y)
		{
			t[1] = (int)(((c - start_y) / (float)(end_y - start_y)) * 64);
			my_mlx_pixel_put(data_()->frame, c, p,
				data_()->textures[0][(int)cc[3]].pixels[t[1]][t[0]]);
		}
		else
		{
			if (c < WINDOW_HEIGHT / 2)
				my_mlx_pixel_put(data_()->frame, c, p, data_()->cel_tex);
			else
				my_mlx_pixel_put(data_()->frame, c, p, data_()->floor_texture);
		}
		c++;
	}
}

void	draw_square(int x, int y, int color, int size)
{
	int	s_y;
	int	s_x;

	s_y = 0;
	while (s_y < size)
	{
		s_x = 0;
		while (s_x < size)
		{
			my_mlx_pixel_put(data_()->frame, s_y + y, s_x + x, color);
			s_x++;
		}
		s_y++;
	}
}

void	draw_minimap(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, WALL, BLOCK_SIZE);
			if (data->map[y][x] == '0' || data->map[y][x] == 'N')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, FLOOR, BLOCK_SIZE);
			x++;
		}
		y++;
	}
}

int	loop_handler(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	apply_changes(data);
	draw_rays_range(-FOV_WIDE, FOV_WIDE, 111, 0xFFFFFF);
	draw_minimap(data);
	draw_player(data->player);
	mlx_put_image_to_window(data_()->mlx_ptr, data_()->window,
		data_()->frame->img_ptr, 0, 0);
	return (0);
}
