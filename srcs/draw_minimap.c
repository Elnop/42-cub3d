/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 00:26:30 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/10 12:54:10 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stddef.h>

void	draw_line(t_image win_image, t_coordinates s, t_coordinates e, int c)
{
	const t_coordinates	d
		= (t_coordinates){abs((int)e.x - (int)s.x), abs((int)e.y - (int)s.y)};
	const t_coordinates	step
		= (t_coordinates){-1 + (s.x < e.x) * 2, -1 + (s.y < e.y) * 2};
	int					err;
	int					e2;

	err = d.x - d.y;
	while (1)
	{
		image_put_px(win_image, s.x, s.y, c);
		if (s.x == e.x && s.y == e.y)
			break ;
		e2 = 2 * err;
		if (e2 > -d.y)
		{
			err -= d.y;
			s.x += step.x;
		}
		if (e2 < d.x)
		{
			err += d.x;
			s.y += step.y;
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

t_ray_impact	get_first_wall(char **map, t_coordinates o, t_coordinates v)
{
	t_coordinates		curr;
	t_coordinates		side_dist;
	t_coordinates		step;
	const t_coordinates	dlt = (t_coordinates){
		fabs(1 / v.x + (!v.x) * 1e30), fabs(1 / v.y + (!v.y) * 1e30)};
	int					side;

	curr = o;

	if (v.x < 0)
	{
		step.x = -1;
		side_dist.x = (o.x - curr.x) * dlt.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (curr.x + 1.0 - o.x) * dlt.x;
	}
	if (v.y < 0)
	{
		step.y = -1;
		side_dist.y = (o.y - curr.y) * dlt.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (curr.y + 1.0 - o.y) * dlt.y;
	}
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += dlt.x;
			curr.x += step.x;
			side = 0;
			if (map[(int)curr.y][(int)curr.x] == '1')
				return ((t_ray_impact){curr.x, curr.y, side_dist.x - dlt.x});
		}
		else
		{
			side_dist.y += dlt.y;
			curr.y += step.y;
			side = 1;
			if (map[(int)curr.y][(int)curr.x] == '1')
				return ((t_ray_impact){curr.x, curr.y, side_dist.y - dlt.y});
		}
	}
}

t_coordinates	rad_to_vect(float angle)
{
	return ((t_coordinates){cosf(angle), sinf(angle)});
}

void	draw_rays(t_app *papp, t_image img)
{
	t_ray_impact	wall;
	float			i;
	int				ray_index;
	float			angle;
	float dist;

	dist = 0;
	ray_index = 0;
	i = -(FOV * M_PI) / 2;
	while (i < (FOV * M_PI) / 2)
	{
		angle = i + papp->player_dir;
		wall = get_first_wall(papp->map, papp->player, rad_to_vect(angle));
		printf("x: %f / y: %f / dist: %f\n", wall.x, wall.y, wall.dist);
		int wall_height;
		int wall_start;
		
		wall_height = WIN_HEIGHT / (wall.dist + (!wall.dist) * 1);
		wall_start = WIN_HEIGHT/2 - wall_height/2;
		//===================================
		draw_line(img, 
			(t_coordinates){
				ray_index,
				wall_start
			},
			(t_coordinates){
				ray_index,
				wall_start + wall_height
			}, 0xFF00FF
		);

		draw_line(img,
			(t_coordinates){
			floor(papp->player.x * papp->mini_map_tile_w + papp->mini_map_tile_w / 2) + 10,
			floor(papp->player.y * papp->mini_map_tile_h + papp->mini_map_tile_h / 2) + 10},
			(t_coordinates){
			floor(wall.x * papp->mini_map_tile_w) + 10,
			floor(wall.y * papp->mini_map_tile_h) + 10},
			0xFF);
		i += (FOV * M_PI)/WIN_WIDTH;
		ray_index++;
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
	draw_rays(papp, win_image);
	draw_rect(win_image, papp->player.x * papp->mini_map_tile_w + 10,
		papp->player.y * papp->mini_map_tile_h + 10, papp->mini_map_tile_w,
		papp->mini_map_tile_h, 0xFFFF);
}
