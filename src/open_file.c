/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:38:17 by dpetrukh          #+#    #+#             */
/*   Updated: 2025/03/05 13:37:57 by dpetrukh         ###   ########.fr       */
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

int	add_texture(char *line, char **mem, int value)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	while (line[i] && ft_strchr(" \n", line[i]))
		i++;
	if (!line[i])
		return (ft_putstr_fd("INVALID PATH TEXTURE INPUT\n", 2), -10);
	len = i;
	while (line[len] && ft_isascii(line[len]) && !ft_strchr(" \n", line[len]))
		len++;
	line[len] = '\0';
	path = ft_strdup(line + i);
	i = open(path, O_RDONLY);
	if (i < 0)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": CAN'T ACCESS TEXTURE PATH FILE:\n", 2);
		free(path);
		return (-10000000);
	}
	close(i);
	*mem = path;
	return (value);
}

int	encode_rgb(byte red, byte green, byte blue)
{
	return (red << 16 | green << 8 | blue);
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

int	error_return(char *str, int value)
{
	ft_putstr_fd(str, 2);
	return (value);
}

int	apply_colors(t_data *data, int colors[3], int value)
{
	if (value == 10000)
		data->cel_tex = encode_rgb(colors[0], colors[1], colors[2]);
	if (value == 100000)
		data->floor_texture = encode_rgb(colors[0], colors[1], colors[2]);
	return (value);
}

//colors[3] are all 0 at the start
//last of colors is colors[3] is for the return value; 1000 or 10000
//i also set to 0
int	add_color(int i, int j, char *line, int colors[4])
{
	if (ft_strlen(line) < 8 || ft_strlen(line) > 14)
		return (error_return("Wrong input of colors\n", -10000000));
	while (line[j] && i < 3)
	{
		colors[i] = ft_coloratoi(&line[j], 0, 0);
		if (colors[i] < 0 || colors[i] > 255)
			return (error_return("Captured bad numbers\n", -10000000));
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

void	exit_error(char *str, int exit_int)
{
	ft_putstr_fd(str, 2);
	exit(exit_int);
}

void	write_close_window(char *str)
{
	ft_putstr_fd(str, 2);
	close_window(data_());
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
		step += add_texture(line, &data_()->textures[WALL_][0].path, 1);
	else if (line[0] != '\n' && !ft_strncmp(line, "SO ", 3))
		step += add_texture(line, &data_()->textures[WALL_][1].path, 10);
	else if (line[0] != '\n' && !ft_strncmp(line, "WE ", 3))
		step += add_texture(line, &data_()->textures[WALL_][2].path, 100);
	else if (line[0] != '\n' && !ft_strncmp(line, "EA ", 3))
		step += add_texture(line, &data_()->textures[WALL_][3].path, 1000);
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
	print_map();
	if (data_()->matrix_width * BLOCK_SIZE > WINDOW_WIDTH)
		exitmap(data_()->map, 1, "Map too big for this proportion\n");
	if (data_()->matrix_height * BLOCK_SIZE > WINDOW_HEIGHT)
		exitmap(data_()->map, 1, "Map too big for this proportion\n");
	check_symbols(data_()->map);
	optimise_map(data_(), data_()->map);
	init_data(data_());
}
