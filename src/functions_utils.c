/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:02:04 by dpetrukh          #+#    #+#             */
/*   Updated: 2025/03/03 13:24:01 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_image(t_image *image)
{
	image->img_ptr = mlx_new_image(data_()->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	image->addr = mlx_get_data_addr(image->img_ptr, &image->bpp,
			&image->line_len, &image->endian);
}

void	init_keys(t_data *data)
{
	static t_binds	binds;

	data->key = &binds;
	data->key->move_up = 0;
	data->key->move_down = 0;
	data->key->move_left = 0;
	data->key->move_right = 0;
	data->key->camera_left = 0;
	data->key->camera_right = 0;
	data->key->esc = 0;
}
