/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 00:26:30 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/03 05:55:19 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stddef.h>


void draw_line(t_image win_image, t_coordinates s, t_coordinates e, int color) {
    int dx = abs((int)e.x - (int)s.x);
    int dy = abs((int)e.y - (int)s.y);
    int sx = (s.x < e.x) ? 1 : -1;
    int sy = (s.y < e.y) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        image_put_px(win_image, s.x, s.y, color);

        if (s.x == e.x && s.y == e.y) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            s.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            s.y += sy;
        }
    }
}

void	draw_rect(t_image win_image, size_t start_x, size_t start_y, size_t width, size_t height, int color)
{
	size_t	y;
	size_t	x;

	y = start_y;
	while (y < height + start_y)
	{
		x = start_x;
		while (x < width + start_x)
		{
			image_put_px(win_image, x, y, color);
			x++;
		}
		y++;
	}
}

t_coordinates	get_first_wall(char **map, t_coordinates origin, double angle)
{
	double			len;
	t_coordinates	wall;

	len = 1;
	wall = (t_coordinates){origin.x + len * cos(angle),
		origin.y + len * -sin(angle)};
	while (map[(int)floor(wall.y)][(int)floor(wall.x)] != '1')
	{
		len++;
		wall = (t_coordinates){origin.x + len * cos(angle),
			origin.y + len * -sin(angle)};
	}
	return (wall);
}

void	draw_rays(t_app *papp, t_image img)
{
	t_coordinates	wall;
	double			i;
	double			angle;

	i = -(FOV * M_PI) / 2;
	while (i < (FOV * M_PI) / 2)
	{
		angle = i + papp->player_dir;
		wall = get_first_wall(papp->map, papp->player, angle);
		draw_line(img,
			(t_coordinates){
			ceil(papp->player.x * papp->mini_map_tile_w + papp->mini_map_tile_w / 2) + 10,
			ceil(papp->player.y * papp->mini_map_tile_h + papp->mini_map_tile_h / 2) + 10},
			(t_coordinates){
			ceil(wall.x * papp->mini_map_tile_w) + 10,
			ceil(wall.y * papp->mini_map_tile_h) + 10},
			0xFF);
		i += 0.001;
	}
}

void	draw_minimap(t_app *papp, t_image win_image)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < array_size(papp->map))
	{
		x = 0;
		while (x < lp_strlen(((char **)papp->map)[y]))
		{
			if (((char **)papp->map)[y][x] == '1')
				draw_rect(win_image, x * papp->mini_map_tile_w + 10,
					y * papp->mini_map_tile_h + 10, papp->mini_map_tile_w,
					papp->mini_map_tile_h, 0xFFFFFF);
			if (((char **)papp->map)[y][x] == '0')
				draw_rect(win_image, x * papp->mini_map_tile_w + 10,
					y * papp->mini_map_tile_h + 10, papp->mini_map_tile_w,
					papp->mini_map_tile_h, 0x666666);
			x++;
		}
		y++;
	}
	draw_rect(win_image, papp->player.x * papp->mini_map_tile_w + 10,
		papp->player.y * papp->mini_map_tile_h + 10, papp->mini_map_tile_w,
		papp->mini_map_tile_h, 0xFFFF);
	draw_rays(papp, win_image);
}
