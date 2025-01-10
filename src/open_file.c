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

// Distribuitor
void	input_file(t_data *data, char *file)
{
	int		fd;
	//char	*line;
	int	start_map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nCouldnt open file\n", 24);
		exit(1);
	}
	//check for NO, SO, WE, EA, C, F first and then check map
	/*while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			//check if everything is loaded
			break;
		}
		if (line[0] != '\n')
		{
			start_map++;
			if (!ft_strncmp(line, "NO", 3))
			{
				//funcao da textura
				//nela verificar se ha uma textura ja loaded
				//caso sim, sair com erro
				printf("Textura norte...\n");
			}
			else if (!ft_strncmp(line, "SO", 3))
			{
				//a textura North da deve estar loaded quando
				//lermos esta
				printf("Textura sul...\n");
			}
			else if (!ft_strncmp(line, "WE", 3))
				printf("Textura oeste...\n");
			else if (!ft_strncmp(line, "EA", 3))
				printf("Textura este...\n");
			else if (!ft_strncmp(line, "C", 2))
				printf("Cor ceu...\n");
			else if (!ft_strncmp(line, "F", 2))
				printf("Cor chao...\n");
			else
			{
			}
		}
	}*/
	//DEFINE WHERES MAP STARTS\n
	start_map = 0;
	map_dimensions(data, fd);
	close(fd);
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
	init_map(data, file, start_map);
}

void	map_dimensions(t_data *data, int fd)
{
	int	i;
	char	*line;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		printf("GETLINE: %s | height: %d\n", line, i);
		if (!line)
			break;
		if (line[0] == '\n') //a nao ser que seja no final?
		{
			write(2, "Error\nMap divided with empty line\n", 34);
			close(fd);
			free(line);
			//CANT BE EXIT, NEED TO FREE TEXTURE PATH
			exit(0);
		}
		if (ft_strlen(line) > (size_t)data->matrix_width)
			data->matrix_width = ft_strlen(line) - 1;
		i++;
		free(line);
	}
	data->matrix_height = i;
	return ;
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

void	fill_spaces(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (i < data->matrix_width)
	{
		if (line[i] == 0 || line[i] == 32)
			line[i] = '1';
		i++;
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
		fill_spaces(data, data->map[i]);
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
	init_data(data_());
	//free(data_()->player);
	//check_player(data_()->map, data_()->player);
	//no need, draw_minimap already handles it
	//map->map[map->p_y][map->p_x] = '0';
}
