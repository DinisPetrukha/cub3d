/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:38:17 by dpetrukh          #+#    #+#             */
/*   Updated: 2025/03/05 15:39:19 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i] != NULL)
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

int	encode_rgb(t_byte red, t_byte green, t_byte blue)
{
	return (red << 16 | green << 8 | blue);
}

int	apply_colors(t_data *data, int colors[3], int value)
{
	if (value == 10000)
		data->cel_tex = encode_rgb(colors[0], colors[1], colors[2]);
	if (value == 100000)
		data->floor_texture = encode_rgb(colors[0], colors[1], colors[2]);
	return (value);
}

// Distribuitor
void	input_file(t_data *data, char *file, int line_nbr, int step)
{
	char	*line;
	int		fd;
	int		start_map;

	start_map = -1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error("Error\nCouldnt open file\n", 1);
	while (step >= 0)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		step = read_file(line, step, &start_map, line_nbr);
		line_nbr++;
		free(line);
	}
	if (step != 111111)
		write_close_window("Error\nNot every step of the map is complete\n");
	if (data->matrix_height < 3)
		write_close_window("Error\nMap is too low\n");
	if (data->matrix_width < 3)
		write_close_window("Error\nMap not wide enough or it doesnt exist\n");
	close(fd);
	init_map(data, file, start_map);
}

void	name_check(char *name)
{
	int	i;
	int	ret;

	i = ft_strlen(name);
	ret = ft_strncmp(&name[i - 4], ".cub", 5);
	if (name[i - 5] == '/')
		ret = 1;
	if (ret)
	{
		ft_putstr_fd("Error\nWrong name\n", 2);
		exit (0);
	}
}
