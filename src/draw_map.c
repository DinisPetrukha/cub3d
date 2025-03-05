/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:03:53 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/21 20:03:53 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_image *image, int y, int x, int color)
{
	char	*dst;

	if (color == -16777216)
		return ;
	dst = image->addr + (y * image->line_len + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_image *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

int	has_decimal(float num)
{
	int	int_num;

	int_num = (int)num;
	if ((float)int_num == num)
		return (0);
	return (1);
}

int	float_equal(float a, float b)
{
	float	difference;
	float	toleration;

	toleration = 0.001;
	difference = a - b;
	if ((-toleration <= difference) && (difference <= toleration))
		return (1);
	return (0);
}

int	return_wall_side(float pos_x, float angle)
{
	int	vertical_collision;

	vertical_collision = has_decimal(pos_x);
	if (vertical_collision && angle < M_PI)
		return (3);
	else if (vertical_collision && angle > M_PI)
		return (2);
	else if (!vertical_collision && (angle < M_PI / 2 || angle > 3 * M_PI / 2))
		return (1);
	return (0);
}

//VE A COLISAO DEPENDENDO DO LADO QUE O RAIO VEM
int	collision(float pos_x, float pos_y, float angle, float coords_arr[4])
{
	int	i;
	int	j;

	i = (int)pos_x;
	j = (int)pos_y;
	if (float_equal((float)i, pos_x) && i != 0 && ((angle > M_PI / 2)
			&& (angle < 3 * M_PI / 2)))
		i--;
	if (float_equal((float)j, pos_y) && j != 0 && ((angle > M_PI)))
		j--;
	if (j < 0 || i < 0)
		return (0);
	if (data_()->map[j][i] == '1')
	{
		coords_arr[0] = pos_y;
		coords_arr[1] = pos_x;
		coords_arr[2] = data_()->map[j][i];
		coords_arr[3] = return_wall_side(pos_x, angle);
		return (1);
	}
	return (0);
}

//CALCULO DE DISTANCIA ENTRE DOIS PONTOS QUAISQUER (X, Y)
float	distance(float x1, float y1, float x2, float y2)
{
	float	sqr_difx;
	float	sqr_dify;
	float	sum;
	float	value;

	sqr_difx = (x2 - x1) * (x2 - x1);
	sqr_dify = (y2 - y1) * (y2 - y1);
	sum = sqr_difx + sqr_dify;
	value = sqrt(sum);
	return (value);
}

//TESTE DE DISTANCIA PARA RAIO VERTICAL
int	vertical_ray(float line[2], float interval, float angle, float crds[4])
{
	float	center[2];
	float	new_x;
	float	y;

	if (interval == 0)
		return (-1);
	center[0] = (data_()->player->x + (PLYRSIZE / 2));
	center[1] = (data_()->player->y + (PLYRSIZE / 2));
	if (interval > 0)
		new_x = ceilf(center[0] / BLOCK_SIZE) * BLOCK_SIZE;
	else
		new_x = floorf(center[0] / BLOCK_SIZE) * BLOCK_SIZE;
	while (1)
	{
		y = line[0] * new_x + line[1];
		if (y < 0 || y > ((data_()->matrix_height - 1) * BLOCK_SIZE)
			|| new_x < 0 || new_x > ((data_()->matrix_width - 1) * BLOCK_SIZE))
			return (-1);
		if (collision(new_x / BLOCK_SIZE, y / BLOCK_SIZE, angle, crds))
			break ;
		new_x += interval;
	}
	return (distance(center[0], center[1], new_x, y));
}

//TESTE DE DISTANCIA PARA RAIO HORIZONTAL
int	horizontal_ray(float line[2], float interval, float angle, float crds[4])
{
	float	center[2];
	float	x;
	float	new_y;

	if (interval == 0)
		return (-1);
	center[0] = (data_()->player->x + (PLYRSIZE / 2));
	center[1] = (data_()->player->y + (PLYRSIZE / 2));
	if (interval > 0)
		new_y = ceilf(center[1] / BLOCK_SIZE) * BLOCK_SIZE;
	else
		new_y = floorf(center[1] / BLOCK_SIZE) * BLOCK_SIZE;
	while (1)
	{
		x = (new_y - line[1]) / line[0];
		if (x < 0 || x > ((data_()->matrix_width) * BLOCK_SIZE)
			|| new_y < 0 || new_y > ((data_()->matrix_height - 1) * BLOCK_SIZE))
			return (-1);
		if (collision(x / BLOCK_SIZE, new_y / BLOCK_SIZE, angle, crds))
			break ;
		new_y += interval;
	}
	return (distance(center[0], center[1], x, new_y));
}

void	float_array_copy(float *dst, float *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

float	fire_rays(float angle, float inc[2], float center[2], float cls_crds[4])
{
	float	rays[2];
	float	line[2];
	float	coords_hor[4];
	float	coords_ver[4];

	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
		return (horizontal_ray((float []){0, 0}, inc[1], angle, cls_crds));
	line[0] = tan(angle);
	line[1] = center[1] - (line[0] * center[0]);
	rays[0] = horizontal_ray(line, inc[1], angle, coords_hor);
	rays[1] = vertical_ray(line, inc[0], angle, coords_ver);
	if ((rays[0] <= rays[1] && rays[0] != -1) || rays[1] == -1)
	{
		float_array_copy(cls_crds, coords_hor, 4);
		return (rays[0]);
	}
	float_array_copy(cls_crds, coords_ver, 4);
	return (rays[1]);
}

//DEVOLVE DISTANCIA DE UM RAIO
float	rainbow(t_player *player, float angle, float collision_cords[4])
{
	float	center[2];
	float	increment[2];

	center[0] = (player->x + (PLYRSIZE / 2));
	center[1] = (player->y + (PLYRSIZE / 2));
	if (sin(angle) > 0)
		increment[1] = BLOCK_SIZE;
	else if (sin(angle) < 0)
		increment[1] = -BLOCK_SIZE;
	else
		increment[1] = 0;
	if (cos(angle) > 0)
		increment[0] = BLOCK_SIZE;
	else if (cos(angle) < 0)
		increment[0] = -BLOCK_SIZE;
	else
		increment[0] = 0;
	return (fire_rays(angle, increment, center, collision_cords));
}

float	rs(float angle)
{
	if (angle < 0)
		return (2 * M_PI + angle);
	if (angle > (2 * M_PI))
		return (angle - (2 * M_PI));
	return (angle);
}

void	draw_line_at_angle(float angle, int color, int x, t_image *image)
{
	float	d;
	float	cls_crds[4];

	color += 1;
	d = rainbow(data_()->player, rs(data_()->player->orient + angle), cls_crds);
	d = fabs(d * cosf(angle));
	if ((int)d >= 0 && ((int)d <= FOV_DEEPNESS))
		draw_bar(0, (BLOCK_SIZE_3D / d) * DISTANCE_TO_SCREEN, x, cls_crds);
	else
		empty_bar(image, x);
}

//ALWAYS ODD NUMBERS OF NUM_RAYS
void	draw_rays_range(float mi, float ma, int rays, int color)
{
	float	angle_step;
	float	current_angle;
	int		i;

	rays += 1;
	angle_step = (ma - mi) / (NUM_RAYS);
	current_angle = mi;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		draw_line_at_angle(current_angle, color, i, data_()->frame);
		current_angle += angle_step;
		i += (WINDOW_WIDTH / NUM_RAYS);
	}
}

//x and y in pixels
bool	verify_corner(int x, int y)
{
	int	top;
	int	bottom;
	int	left;
	int	right;

	top = my_mlx_pixel_get(data_()->frame, x, y - 1);
	bottom = my_mlx_pixel_get(data_()->frame, x, y + 1);
	left = my_mlx_pixel_get(data_()->frame, x - 1, y);
	right = my_mlx_pixel_get(data_()->frame, x + 1, y);
	if (top == WALL && right == WALL)
		return (true);
	if (top == WALL && left == WALL)
		return (true);
	if (bottom == WALL && right == WALL)
		return (true);
	if (bottom == WALL && left == WALL)
		return (true);
	return (false);
}

void	draw_line_map(t_player *player, float angle, int color, t_image *image)
{
	int	center[2];
	int	line[2];
	int	i;
	int	hit_wall_flag;

	center[0] = player->y + (PLYRSIZE / 2);
	center[1] = player->x + (PLYRSIZE / 2);
	i = 0;
	hit_wall_flag = 0;
	while (i < FOV_DEEPNESS && hit_wall_flag == 0)
	{
		line[0] = center[0] + i * sin(player->orient + angle);
		line[1] = center[1] + i * cos(player->orient + angle);
		if (verify_corner(line[1], line[0]))
			break ;
		if (!is_wall_line(data_(), line[0], line[1], &hit_wall_flag))
			my_mlx_pixel_put(image, line[0], line[1], color);
		i++;
	}
}

void	draw_player_rays(float angle_min, float angle_max, int nrays, int color)
{
	float	angle_step;
	float	current_angle;
	int		i;

	angle_step = (angle_max - angle_min) / (nrays - 1);
	current_angle = angle_min;
	i = 0;
	while (i < nrays)
	{
		draw_line_map(data_()->player, current_angle, color, data_()->frame);
		current_angle += angle_step;
		i++;
	}
}

void	draw_player(t_player *player)
{
	if (data_()->first_render == 0)
	{
		player->y = (player->y * BLOCK_SIZE);
		player->x = (player->x * BLOCK_SIZE);
		data_()->first_render = 1;
	}
	draw_square(player->x, player->y, 0x00FF0000, PLYRSIZE);
	draw_player_rays(-FOV_WIDE, FOV_WIDE, FOV_DEEPNESS, RAY);
}

//ceil color and floor color
void	draw_half(t_image *image, int ccolor, int fcolor)
{
	int	cur_x;
	int	cur_y;

	cur_y = 0;
	while (cur_y < WINDOW_HEIGHT / 2)
	{
		cur_x = 0;
		while (cur_x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(image, cur_y, cur_x, ccolor);
			cur_x++;
		}
		cur_y++;
	}
	while (cur_y < WINDOW_HEIGHT)
	{
		cur_x = 0;
		while (cur_x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(image, cur_y, cur_x, fcolor);
			cur_x++;
		}
		cur_y++;
	}
}

void	empty_bar(t_image *image, int pos_x)
{
	int	pos_y;

	pos_y = 0;
	while (pos_y < WINDOW_HEIGHT / 2)
	{
		my_mlx_pixel_put(image, pos_y, pos_x, data_()->cel_tex);
		pos_y++;
	}
	while (pos_y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(image, pos_y, pos_x, data_()->floor_texture);
		pos_y++;
	}
}

float	wall_x(float collision_cords[4])
{
	if (fabs(collision_cords[0] - floor(collision_cords[0])) < 0.0001)
		return (collision_cords[1] - floor(collision_cords[1]));
	else
		return (collision_cords[0] - floor(collision_cords[0]));
}

void	draw_bar(int c, float bar_size, int p, float cc[4])
{
	int		start_y;
	int		end_y;
	int		t[2];

	start_y = (WINDOW_HEIGHT / 2) - ((int)bar_size / 2);
	end_y = (WINDOW_HEIGHT / 2) + ((int)bar_size / 2);
	t[0] = (int)(wall_x(cc) * TEXTURE_SIZE) % TEXTURE_SIZE;
	while (c < WINDOW_HEIGHT)
	{
		if (c >= start_y && c < end_y)
		{
			t[1] = (int)(((c - start_y) / (float)(end_y - start_y)) * 64);
			my_mlx_pixel_put(data_()->frame, c, p,
				data_()->textures[0][(int)cc[3]].pixels[t[1]][t[0]]);
		}
		else
		{
			if (c < WINDOW_HEIGHT / 2)
				my_mlx_pixel_put(data_()->frame, c, p, data_()->cel_tex);
			else
				my_mlx_pixel_put(data_()->frame, c, p, data_()->floor_texture);
		}
		c++;
	}
}

void	draw_square(int x, int y, int color, int size)
{
	int	s_y;
	int	s_x;

	s_y = 0;
	while (s_y < size)
	{
		s_x = 0;
		while (s_x < size)
		{
			my_mlx_pixel_put(data_()->frame, s_y + y, s_x + x, color);
			s_x++;
		}
		s_y++;
	}
}

void	draw_minimap(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, WALL, BLOCK_SIZE);
			if (data->map[y][x] == '0' || data->map[y][x] == 'N')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, FLOOR, BLOCK_SIZE);
			x++;
		}
		y++;
	}
}

int	loop_handler(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	apply_changes(data);
	draw_rays_range(-FOV_WIDE, FOV_WIDE, 111, 0xFFFFFF);
	draw_minimap(data);
	draw_player(data->player);
	mlx_put_image_to_window(data_()->mlx_ptr, data_()->window,
		data_()->frame->img_ptr, 0, 0);
	return (0);
}
