/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:47:16 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/27 14:47:16 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	exitmap(char **map, int ret, char *msg)
{
	ft_putstr_fd(msg, 2);
	clean_textures(data_());
	free_map(map);
	exit(ret);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	is_protected(char **map, int j, int i)
{
	//above
	//printf("j: %d i: %d: %c\n", j, i, map[j][i]);
	if (j == 0 || map[j - 1][i] == 32)
		return (0);
	//below
	if (j == data_()->matrix_height - 1 || map[j + 1][i] == 32)
		return (0);
	//left
	if (i == 0 || map[j][i - 1] == 32)
		return (0);
	//right
	if (i == data_()->matrix_width - 1 || map[j][i + 1] == 32)
		return (0);
	return (1);
}

void	optimise_map(t_data *data, char **map)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->matrix_height)
	{
		i = 0;
		while (i < data->matrix_width)
		{
			if (map[j][i] == 0 || map[j][i] == 32)
				map[j][i] = '1';
			i++;
		}
		j++;
	}
}

void	check_symbols(char **map)
{
	int	i;
	int	j;
	int	c;

	j = 0;
	while (j < data_()->matrix_height)
	{
		i = 0;
		//printf("MAP[%d][0]: %d\n", j, map[j][0]);
		//if (map[j][0] == '\n')
		if (!map[j][0])
			exitmap(map, 1, "Error\nGap in map\n");
		while (map[j][i])
		{
			c = map[j][i];
			//if (!map[i][j + 1] && c != '\n')
			//	exitmap(map, 1, "Error\nNo new line\n");
			if (!(c == 32 || c == 10 || c == '0' || c == '1'
				|| c == 'S' || c == 'W' || c == 'N' || c == 'E'))
				exitmap(map, 1, "Error\nWrong letter\n");
			//just check spaces and player for protection
			if (c != 32 && c != '1' && c != 10)
			{

				if (!(is_protected(map, j, i)))
				{
					printf("i: %d j: %d %c\n", j, i, map[j][i]);
					exitmap(map, 1, "Error\nNot Protected\n");
				}
			}
			i++;
		}
		j++;
	}
}

void	check_player(char **map, t_player *player)
{
	int	player_n;
	int	i;
	int	j;

	j = 0;
	player_n = 0;
	while (j < data_()->matrix_height)
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'N')
				player->orient = 3 * M_PI / 2; // 90º
			if (map[j][i] == 'S')
				player->orient = M_PI / 2; // 270º
			if (map[j][i] == 'W')
				player->orient = M_PI; // 180º
			if (map[j][i] == 'E')
				player->orient = 0;
			if (map[j][i] > 'A' && map[j][i] < 'Z')
			{
				player->y = j + 0.5;
				player->x = i + 0.5;
				data_()->map[j][i] = '0';
				player_n++;
			}
			i++;
		}
		j++;
	}
	if (player_n != 1)
		exitmap(map, 0, "Error\nMultiple Players\n");
	//DOUBLE CHECK THIS EXITMAP, PROBABLY LEAKS
}
