/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:38:17 by dpetrukh          #+#    #+#             */
/*   Updated: 2025/03/03 11:27:51 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
/*
// Função para calcular a altura do mapa
void	set_map_size(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > data_()->matrix_width)
			data_()->matrix_width = x;
		y++;
	}
	data_()->matrix_height = y;
}*/

void free_mat(char **mat)
{
	int i = 0;

	while (mat[i] != NULL)
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}
/*
char	**read_map(int fd)
{
	char	*map_inline;
	char	*line;
	char	*tmp;
	char	**map_index;

	line = NULL;
	map_inline = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp = map_inline;
		map_inline = my_ft_strjoin(map_inline, line);
		free(line);
		free(tmp);
	}
	map_index = ft_split(map_inline, '\n');
	free(map_inline);
	if (!map_index)
	{
		ft_putstr_fd("Error\nMap is empty\n", 2);
		return (NULL);
	}
	set_map_size(map_index);
	if (data_()->matrix_height < 3)
		exitmap(map_index, 1, "Error\nMap is too low\n");
	return (map_index);
}

int	file_name_verification(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '.')
			break ;
		i++;
	}
	if (!ft_strncmp(&path[i], ".cub", 5))
		return (1);
	return (0);
}



// Return 1 if all correct
// Return 0 if not correct and print the error
int	open_file(char *path)
{
	int	fd;

	//Check if ends with .cub
	if (!file_name_verification(path))
	{
		ft_putstr_fd("Error\nInvalid file name\n", 2);
		exit(1);
	}
	//Open Map
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nNot able to open the file:");
		exit(1);
	}
	//Read Map
	data_()->map = read_map(fd);
	if (data_()->map == NULL)
		exit(1);
	print_map(); // <-- Test
	//Check if valid map
	check_symbols(data_()->map);
	init_data(data_());
	//Load all necessary data to t_data struct

	//Return 1 if all good
	return (1);
}*/

/////////////////
///NEW VERSION///
/////////////////

/*
//TEXTURE.CUB
void	path_and_color(int fd)
{
	int	texture_loaded[4];
	int	ceiling_floor[2];
	int	i;

	i = 0;
	while (i < 4)
	{
		texture_loaded[i] = 0;
		i++;
	}
	ceiling_floor[0] = 0;
	ceiling_floor[1] = 0;
	while (1)
	{
		line = get_next_line(fd);
			free(line);
	}
}*/

int	printf_return(char *str, int num)
{
	printf("%s", str);
	return (num);
}

int	add_texture(char *line, char **mem)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	while (line[i] && ft_strchr(" \n", line[i]))
		i++;
	if (!line[i])
		return (printf_return("INVALID PATH TEXTURE INPUT\n", -10));
	len = i;
	while (line[len] && ft_isascii(line[len]) && !ft_strchr(" \n", line[len]))
		len++;
	line[len] = '\0';
	path = ft_strdup(line + i);
	i = open(path, O_RDONLY);
	if (i < 0)
	{
		printf("CAN'T ACCESS TEXTURE PATH FILE:\n%s\n", path);
		free(path);
		return (-10);
	}
	close(i);
	*mem = path;
	return (1);
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
			break;
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
	if (value == 1)
		data->ceiling_texture = encode_rgb(colors[0], colors[1], colors[2]);
	if (value == 2)
		data->floor_texture = encode_rgb(colors[0], colors[1], colors[2]);
	return (1);
}

//colors[3] are all 0 at the start
//i also set to 0
int	add_color(int i, char *line, int value, int colors[3])
{
	int	j;

	if (ft_strlen(line) < 8 || ft_strlen(line) > 14)
		return(error_return("Wrong input of colors\n", -10));
	j = 2;
	while (line[j] && i < 3)
	{
		colors[i] = ft_coloratoi(&line[j], 0, 0);
		if (colors[i] < 0 || colors[i] > 255)
			return (error_return("Captured bad numbers\n", -10));
		while (line[j])
		{
			if (line[j] < '0' || line[j] > '9')
			{
				if (line[j] == ',' || line[j] == '\n')
				{
					j++;
					break ;
				}
				return (-10);
			}
			j++;
		}
		i++;
	}
	return(apply_colors(data_(), colors, value), 1);
}

void	exit_error(char *str, int exit_int)
{
	ft_putstr_fd(str, 2);
	exit(exit_int);
}

void write_close_window(char *str)
{
	ft_putstr_fd(str, 2);
	close_window(data_());
}

int	read_file(char *line, int step, int *start_map, int line_nbr)
{
	if (line[0] != '\n' && !ft_strncmp(line, "NO ", 3) && step == 1)
		step += add_texture(line, &data_()->textures[WALL_][0].path);
	else if (line[0] != '\n' && !ft_strncmp(line, "SO ", 3) && step == 2)
		step += add_texture(line, &data_()->textures[WALL_][1].path);
	else if (line[0] != '\n' && !ft_strncmp(line, "WE ", 3) && step == 3)
		step += add_texture(line, &data_()->textures[WALL_][2].path);
	else if (line[0] != '\n' && !ft_strncmp(line, "EA ", 3) && step == 4)
		step += add_texture(line, &data_()->textures[WALL_][3].path);
	else if (line[0] != '\n' && !ft_strncmp(line, "C", 1) && step == 5)
		step += add_color(0, line, 1, (int[]){0, 0, 0});
	else if (line[0] != '\n' && !ft_strncmp(line, "F", 1) && step == 6)
		step += add_color(0, line, 2, (int[]){0, 0, 0});
	else if (line[0] != '\n' && step == 7)
	{
		if (*start_map == -1)
			*start_map = line_nbr;
		if (ft_strlen(line) > (size_t)data_()->matrix_width)
			data_()->matrix_width = ft_strlen(line) - 1;
		data_()->matrix_height++;
	}
	return (step);
}

// Distribuitor
void	input_file(t_data *data, char *file, int line_nbr, int step)
{
	int		fd;
	char	*line;
	int	start_map;

	start_map = -1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error("Error\nCouldnt open file\n", 1);
	while (step > 0)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		step = read_file(line, step, &start_map, line_nbr);
		line_nbr++;
		free(line);
	}
	if (step != 7)
		write_close_window("Error\nNot every step of the map is complete\n");
	if (data->matrix_height < 3)
		write_close_window("Error\nMap is too low\n");
	if (data->matrix_width < 3)
		write_close_window("Error\nMap not wide enought or it doesnt exist\n");
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
		write(2, "Error\nWrong name\n", 17);
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
	int	fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nCouldnt open file\n", 24);
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

//DIDN'T HANDLE SUBJECT INPUT, JUST SIMPLE SO_LONG MAP
void	map_constructor(char *file)
{
	name_check(file);
	//texture_check
	//colour_check
	data_()->ceiling_texture = 0;
	data_()->floor_texture = 0;
	input_file(data_(), file, 0, 1);
	print_map();
	//map_count_row(player, file);
	//init_map(player, file);
	if (data_()->matrix_width * BLOCK_SIZE > WINDOW_WIDTH)
		exitmap(data_()->map, 1, "Map too big\n");
	if (data_()->matrix_height * BLOCK_SIZE > WINDOW_HEIGHT)
		exitmap(data_()->map, 1, "Map too big\n");
	check_symbols(data_()->map);
	optimise_map(data_(), data_()->map);
	init_data(data_());
	//free(data_()->player);
	//check_player(data_()->map, data_()->player);
	//no need, draw_minimap already handles it
	//map->map[map->p_y][map->p_x] = '0';
}
