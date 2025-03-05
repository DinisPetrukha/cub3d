/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:40:54 by sephilip          #+#    #+#             */
/*   Updated: 2025/03/05 14:41:47 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//VE A COLISAO DEPENDENDO DO LADO QUE O RAIO VEM
int	collision(float pos_x, float pos_y, float angle, float coords_arr[4])
{
	int	i;
	int	j;

	i = (int)pos_x;
	j = (int)pos_y;
	if (float_equal((float)i, pos_x) && i != 0 && ((angle > M_PI / 2)
			&& (angle < 3 * M_PI / 2)))
		i--;
	if (float_equal((float)j, pos_y) && j != 0 && ((angle > M_PI)))
		j--;
	if (j < 0 || i < 0)
		return (0);
	if (data_()->map[j][i] == '1')
	{
		coords_arr[0] = pos_y;
		coords_arr[1] = pos_x;
		coords_arr[2] = data_()->map[j][i];
		coords_arr[3] = return_wall_side(pos_x, angle);
		return (1);
	}
	return (0);
}

void	float_array_copy(float *dst, float *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

float	rs(float angle)
{
	if (angle < 0)
		return (2 * M_PI + angle);
	if (angle > (2 * M_PI))
		return (angle - (2 * M_PI));
	return (angle);
}

//x and y in pixels
bool	verify_corner(int x, int y)
{
	int	top;
	int	bottom;
	int	left;
	int	right;

	top = my_mlx_pixel_get(data_()->frame, x, y - 1);
	bottom = my_mlx_pixel_get(data_()->frame, x, y + 1);
	left = my_mlx_pixel_get(data_()->frame, x - 1, y);
	right = my_mlx_pixel_get(data_()->frame, x + 1, y);
	if (top == WALL && right == WALL)
		return (true);
	if (top == WALL && left == WALL)
		return (true);
	if (bottom == WALL && right == WALL)
		return (true);
	if (bottom == WALL && left == WALL)
		return (true);
	return (false);
}

float	wall_x(float collision_cords[4])
{
	if (fabs(collision_cords[0] - floor(collision_cords[0])) < 0.0001)
		return (collision_cords[1] - floor(collision_cords[1]));
	else
		return (collision_cords[0] - floor(collision_cords[0]));
}
