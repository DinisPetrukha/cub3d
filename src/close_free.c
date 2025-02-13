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

void	clean_textures(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	//NUMBER OF ELEMENTS
	while (i < NUMBER_OF_TEXTURES)
	{
		j = 0;
		while (j < 4)
		{

			if (data->textures[i][j].path)
			{
				free(data->textures[i][j].path);
				data->textures[i][j].path = NULL;
			}
			if (data->textures[i][j].img_ptr)
			{
				mlx_destroy_image(data->mlx_ptr, data->textures[i][j].img_ptr);
				data->textures[i][j].img_ptr = NULL;
			}
			j++;
		}
		i++;
	}
}


int	close_window(t_data *data)
{
	int	i;
	int	j;


	if (data->map)
		free_map(data->map);
	i = 0;
	while (i < NUMBER_OF_TEXTURES)
	{
		j = 0;
		while (j < 4)
		{

			if (data->textures[i][j].path)
			{
				free(data->textures[i][j].path);
				data->textures[i][j].path = NULL;
			}
			if (data->textures[i][j].img_ptr)
			{
				mlx_destroy_image(data->mlx_ptr, data->textures[i][j].img_ptr);
				data->textures[i][j].img_ptr = NULL;
			}
			j++;
		}
		i++;
	}
	if (data->mlx_ptr)
	{
		if (data->frame)
			mlx_destroy_image(data->mlx_ptr, data->frame->img_ptr);
		if (data->window)
			mlx_destroy_window(data->mlx_ptr, data->window);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
}
