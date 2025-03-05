/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:43:39 by sephilip          #+#    #+#             */
/*   Updated: 2025/03/05 14:49:49 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_isspace(int c)
{
	return (((c >= 9) && (c <= 13)) || (c == 32));
}

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

int	only_spaces(char *line)
{
	int	i;
	int	only;

	i = 0;
	only = 1;
	if (line[0] && line[0] == '\n')
		return (only);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			only = 0;
		i++;
	}
	return (only);
}
