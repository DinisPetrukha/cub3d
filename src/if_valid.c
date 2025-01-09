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
	free_map(map, ret);
}

void	free_map(char **map, int ret)
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
	exit(ret);
}

int	is_protected(char **map, int y, int x)
{
	//above
	if (y == 0 || ft_strlen(map[y - 1]) - 1 <= (size_t)x
		|| map[y - 1][x] == 32)
		return (0);
	//below
	if (y == data_()->matrix_height - 1
		|| ft_strlen(map[y + 1]) - 1 <= (size_t)x
		|| map[y + 1][x] == 32)
		return (0);
	//left
	if (x == 0 || map[y][x - 1] == 32)
		return (0);
	//right
	if (x == data_()->matrix_width - 1 || map[y][x + 1] == 32
		|| map[y][x + 1] == '\n')
			return (0);
	return (1);
}

void	check_symbols(char **map)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	while (i < data_()->matrix_height)
	{
		j = 0;
		if (map[i][0] == '\n')
			exitmap(map, 1, "Error\nGap in map\n");
		while (map[i][j])
		{
			c = map[i][j];
			// if (!map[i][j + 1] && c != '\n')
			// 	exitmap(map, 1, "Error\nNo new line\n");
			if (!(c == 32 || c == 10 || c == '0' || c == '1'
				|| c == 'S' || c == 'W' || c == 'N' || c == 'E'))
				exitmap(map, 1, "Error\nWrong letter\n");
			//just check spaces and player for protection
			if (c != 32 && c != '1' && c != 10)
			{
				if (!(is_protected(map, i, j)))
					exitmap(map, 1, "Error\nNot Protected\n");
			}
			j++;
		}
		i++;
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
}
