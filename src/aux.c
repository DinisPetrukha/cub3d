/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:32:41 by sephilip          #+#    #+#             */
/*   Updated: 2025/03/05 14:32:41 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_image *image, int y, int x, int color)
{
	char	*dst;

	if (color == -16777216)
		return ;
	dst = image->addr + (y * image->line_len + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_image *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

int	has_decimal(float num)
{
	int	int_num;

	int_num = (int)num;
	if ((float)int_num == num)
		return (0);
	return (1);
}

int	float_equal(float a, float b)
{
	float	difference;
	float	toleration;

	toleration = 0.001;
	difference = a - b;
	if ((-toleration <= difference) && (difference <= toleration))
		return (1);
	return (0);
}

//CALCULO DE DISTANCIA ENTRE DOIS PONTOS QUAISQUER (X, Y)
float	distance(float x1, float y1, float x2, float y2)
{
	float	sqr_difx;
	float	sqr_dify;
	float	sum;
	float	value;

	sqr_difx = (x2 - x1) * (x2 - x1);
	sqr_dify = (y2 - y1) * (y2 - y1);
	sum = sqr_difx + sqr_dify;
	value = sqrt(sum);
	return (value);
}
