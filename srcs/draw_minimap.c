/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 00:26:30 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/12 03:35:41 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stddef.h>

void	draw_rect(t_image win_image, t_coor s, t_coor lengths, int color)
{
	size_t	y;
	size_t	x;

	y = s.y;
	while (y < lengths.y + s.y)
	{
		x = s.x;
		while (x < lengths.x + s.x)
		{
			image_put_px(win_image, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_rays(t_app *papp, t_image img)
{
	t_ray	wall;
	float			i;
	long			ray_index;
	float			angle;

	ray_index = 0;
	i = -(FOV * M_PI) / 2;
	while (i <= (FOV * M_PI) / 2)
	{
		angle = i + papp->p_dir;
		wall = get_first_wall(papp->map, papp->p, rad_to_vect(angle));
		draw_line(img,
			(t_coor){
			floor(papp->p.x * papp->tile_w) + 10,
			floor(papp->p.y * papp->tile_h) + 10},
			(t_coor){
			floor(wall.x * papp->tile_w) + 10,
			floor(wall.y * papp->tile_h) + 10},
			0xFF);
		i += (FOV * M_PI) / WIN_WIDTH;
		ray_index++;
	}
}

void	draw_minimap(t_app *papp, t_image win_image)
{
	t_coor	i;

	i.y = 0;
	while (i.y < array_size(papp->map))
	{
		i.x = 0;
		while (i.x < lp_strlen(((char **)papp->map)[(int)i.y]))
		{
			if (((char **)papp->map)[(int)i.y][(int)i.x] == '1')
				draw_rect(win_image, (t_coor){i.x * papp->tile_w + 10,
					i.y * papp->tile_h + 10},
					(t_coor){papp->tile_w, papp->tile_h}, 0xFFFFFF);
			if (((char **)papp->map)[(int)i.y][(int)i.x] == '0')
				draw_rect(win_image, (t_coor){i.x * papp->tile_w + 10,
					i.y * papp->tile_h + 10},
					(t_coor){papp->tile_w, papp->tile_h}, 0x666666);
			i.x++;
		}
		i.y++;
	}
	draw_rays(papp, win_image);
	draw_rect(win_image, (t_coor){papp->p.x * papp->tile_w - papp->tile_w / 4 + 10,
		papp->p.y * papp->tile_h - papp->tile_h / 4 + 10},
		(t_coor){papp->tile_w / 2, papp->tile_h / 2}, 0xFFFF);
}
