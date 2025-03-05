/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sephilip <sephilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:25:32 by sephilip          #+#    #+#             */
/*   Updated: 2025/03/05 16:58:04 by sephilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	map_copy(char *line, int fd, t_data *data, int i)
{
	while (i < data_()->matrix_height)
	{
		line = get_next_line(fd);
		data->map[i] = (char *)ft_calloc((data->matrix_width), sizeof(char *));
		ft_strlcpy(data->map[i], line, ft_strlen(line));
		free(line);
		i++;
	}
}

void	init_map(t_data *data, char *file, int start_map)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nCouldnt open file\n", 2);
		exit(1);
	}
	while (start_map)
	{
		line = get_next_line(fd);
		start_map--;
		free(line);
	}
	data->map = (char **)ft_calloc((data->matrix_height + 1), sizeof(char *));
	if (!data->map)
	{
		close(fd);
		exit(1);
	}
	map_copy(line, fd, data, 0);
	close(fd);
}

void	map_constructor(char *file)
{
	name_check(file);
	data_()->cel_tex = 0;
	data_()->floor_texture = 0;
	input_file(data_(), file, 0, 0);
	if (data_()->matrix_width * BLOCK_SIZE > WINDOW_WIDTH)
		exitmap(data_()->map, 1, "Map too big for this proportion\n");
	if (data_()->matrix_height * BLOCK_SIZE > WINDOW_HEIGHT)
		exitmap(data_()->map, 1, "Map too big for this proportion\n");
	check_symbols(data_()->map);
	optimise_map(data_(), data_()->map);
	init_data(data_());
}

void	map_height_count(char *line, int *start_map, int line_nbr)
{
	if (line[0] != '\n' || *start_map != -1)
	{
		if (*start_map == -1)
			*start_map = line_nbr;
		if (ft_strlen(line) > (size_t)data_()->matrix_width)
			data_()->matrix_width = ft_strlen(line) - 1;
		data_()->matrix_height++;
	}
}

// 0000000 1111111 1100000
int	read_file(char *line, int step, int *start_map, int line_nbr)
{
	int	old_step;

	old_step = step;
	if (line[0] != '\n' && !ft_strncmp(line, "NO ", 3))
		step += add_texture(line, &data_()->textures[WALL_][2].path, 1);
	else if (line[0] != '\n' && !ft_strncmp(line, "SO ", 3))
		step += add_texture(line, &data_()->textures[WALL_][3].path, 10);
	else if (line[0] != '\n' && !ft_strncmp(line, "WE ", 3))
		step += add_texture(line, &data_()->textures[WALL_][0].path, 100);
	else if (line[0] != '\n' && !ft_strncmp(line, "EA ", 3))
		step += add_texture(line, &data_()->textures[WALL_][1].path, 1000);
	else if (line[0] != '\n' && !ft_strncmp(line, "C", 1))
		step += add_color(0, 2, line, (int []){0, 0, 0, 10000});
	else if (line[0] != '\n' && !ft_strncmp(line, "F", 1))
		step += add_color(0, 2, line, (int []){0, 0, 0, 100000});
	else if (step == 111111)
		map_height_count(line, start_map, line_nbr);
	if (line[0] != '\n' && old_step == step && step != 111111)
		return (-10000000);
	return (step);
}
