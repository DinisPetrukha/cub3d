/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:29:22 by sephilip          #+#    #+#             */
/*   Updated: 2025/03/05 17:48:17 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//colors[3] are all 0 at the start
//last of colors is colors[3] is for the return value; 1000 or 10000
//i also set to 0
int	add_color(int i, int j, char *line, int colors[4])
{
	if (ft_strlen(line) < 8 || ft_strlen(line) > 14)
		return (free(line), \
			write_close_window("Error\nWrong input of colors\n"), -10);
	while (line[j] && i < 3)
	{
		colors[i] = ft_coloratoi(&line[j], 0, 0);
		if (colors[i] < 0 || colors[i] > 255)
			return (free(line), \
				write_close_window("Error\nCaptured bad numbers\n"), -10);
		while (line[j])
		{
			if (line[j] < '0' || line[j] > '9')
			{
				if (line[j] == ',' || line[j] == '\n')
				{
					j++;
					break ;
				}
				return (-10000000);
			}
			j++;
		}
		i++;
	}
	return (apply_colors(data_(), colors, colors[3]));
}

//int res, int separator must always be set to 0
int	ft_coloratoi(const char *nptr, int res, int separator)
{
	char	*nbr;
	int		i;

	i = 0;
	nbr = (char *)nptr;
	while (((nbr[i] >= 9) && (nbr[i] <= 13)) || nbr[i] == 32)
		i++;
	if (!nbr[i])
		return (-1);
	while (nbr[i])
	{
		if (nbr[i] >= 48 && nbr[i] <= 57)
			res = res * 10 + nbr[i] - 48;
		else if (nbr[i] == ',' || nbr[i] == '\n')
		{
			separator++;
			break ;
		}
		else
			return (-1);
		i++;
	}
	if (!i && separator)
		return (-1);
	return (res);
}

int	add_texture(char *line, char **mem, int value)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	while (line[i] && ft_strchr(" \n", line[i]))
		i++;
	if (!line[i])
		return (free(line), \
			write_close_window("Error\nInvalid path texture\n"), -10);
	len = i;
	while (line[len] && ft_isascii(line[len]) && !ft_strchr(" \n", line[len]))
		len++;
	line[len] = '\0';
	path = ft_strdup(line + i);
	i = open(path, O_RDONLY);
	if (i < 0)
	{
		return (free(line), free(path), \
			write_close_window("Error\nCant access texture\n"), -10);
	}
	close(i);
	*mem = path;
	return (value);
}
