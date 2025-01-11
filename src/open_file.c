/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:38:17 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/12/09 09:49:58 by dpetrukh         ###   ########.fr       */
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

int	add_texture(int value)
{
	printf("ADD_TEXTURE VALUE: %d\n", value);
	return (1);
	//error
	//return -10
}

int	add_color(int value)
{
	printf("ADD_COLOR VALUE: %d\n", value);
	return (1);
	//error
	//return -10
}


// Distribuitor
void	input_file(t_data *data, char *file)
{
	int		fd;
	int		step;
	char	*line;
	int	start_map;
	int	line_nbr;

	step = 1;
	start_map = -1;
	line_nbr = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nCouldnt open file\n", 24);
		exit(1);
	}
	//check for NO, SO, WE, EA, C, F first and then check map
	while (step > 0)
	{
		line = get_next_line(fd);
		printf("STEP: %d READ: %s\n", step, line);
		if (!line)
			break;
		if (line[0] != '\n' && !ft_strncmp(line, "NO", 2) && step == 1)
		{
			//para cada:
			//add_texture devolve 1 em caso de sucesso e -100 
			//funcao da textura
			printf("Textura norte...\n");
			step += add_texture(1);
		}
		else if (line[0] != '\n' && !ft_strncmp(line, "SO", 2) && step == 2)
		{
			printf("Textura sul...\n");
			step += add_texture(2);
		}
		else if (line[0] != '\n' && !ft_strncmp(line, "WE", 2) && step == 3)
		{
			printf("Textura oeste...\n");
			step += add_texture(3);
		}
		else if (line[0] != '\n' && !ft_strncmp(line, "EA", 2) && step == 4)
		{
			printf("Textura este...\n");
			step += add_texture(4);
		}
		else if (line[0] != '\n' && !ft_strncmp(line, "C", 1) && step == 5)
		{
			printf("Cor ceu...\n");
			step += add_color(1);

		}
		else if (line[0] != '\n' && !ft_strncmp(line, "F", 1) && step == 6)
		{
			printf("Cor chao...\n");
			step += add_color(1);
		}
		else if (line[0] != '\n' && step == 7)
		{
			if (start_map == -1)
				start_map = line_nbr;
			if (ft_strlen(line) > (size_t)data->matrix_width)
				data->matrix_width = ft_strlen(line) - 1;
			data->matrix_height++;
		}
		line_nbr++;
	}
	if (step != 7)
	{
		printf("ERROR: NOT EVERY STEP OF THE MAP IS COMPLETE\n");
		//CANT BE EXIT, NEED TO FREE TEXTURE PATH
		exit(0);

	}
	if (data->matrix_height < 3)
	{
		write(2, "Error\nMap is too low\n", 21);
		//CANT BE EXIT, NEED TO FREE TEXTURE PATH
		exit(0);
	}
	if (data->matrix_width < 3)
	{
		write(2, "Error\nMap not wide enought or it doesnt exist\n", 47);
		//CANT BE EXIT, NEED TO FREE TEXTURE PATH
		exit(0);
	}
	close(fd);
	printf("START MAP: %d\n", start_map);
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

void	init_map(t_data *data, char *file, int start_map)
{
	int	fd;
	int	i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nCouldnt open file\n", 24);
		exit(1);
	}
	//PROBABLY WRONG
	while (start_map)
	{
		printf("START_MAP: %d\n", start_map);
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
	i = 0;
	while (i < data->matrix_height)
	{
		line = get_next_line(fd);
		data->map[i] = (char *)ft_calloc((data->matrix_width), sizeof(char *));
		ft_strlcpy(data->map[i], line, ft_strlen(line));
		//fill_spaces(data, data->map[i]);
		free(line);
		i++;
	}
	close(fd);
}

//DIDN'T HANDLE SUBJECT INPUT, JUST SIMPLE SO_LONG MAP
void	map_constructor(char *file)
{
	name_check(file);
	//texture_check
	//colour_check
	input_file(data_(), file);
	print_map();
	//map_count_row(player, file);
	//init_map(player, file);
	check_symbols(data_()->map);
	optimise_map(data_(), data_()->map);
	init_data(data_());
	//free(data_()->player);
	//check_player(data_()->map, data_()->player);
	//no need, draw_minimap already handles it
	//map->map[map->p_y][map->p_x] = '0';
}
