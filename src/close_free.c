/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:02:12 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/21 20:02:12 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// TEMPORARIAMENTE PROBLEMA DE SEG FAULT AO CLICAR NA CRUZ
int	close_window(t_data *data)
{
	int	i;
	int	j;

	free_map(data->map, 1);
	mlx_destroy_image(data->mlx_ptr, data->frame->img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->window);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	i = 0;
	while (i < NUMBER_OF_TEXTURES)
	{
		j = 0;
		while (data->textures[i][j].path)
		{
			if (data->textures[i][j].path)
				free(data->textures[i][j].path);
			j++;
		}
		i++;
	}
	return (0);
}