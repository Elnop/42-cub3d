/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 00:26:30 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/17 05:39:01 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	size_t	i;
	t_ray	*rays;

	rays = ray_cast(papp);
	i = 0;
	while (i < array_size(rays))
	{
		draw_line(img,
			(t_coor){
			floor(rays[i].ox * papp->tile_w) + 10,
			floor(rays[i].oy * papp->tile_h) + 10},
			(t_coor){
			floor(rays[i].wx * papp->tile_w + papp->tile_w / 2) + 10,
			floor(rays[i].wy * papp->tile_h + papp->tile_h / 2) + 10},
			0xFF);
		i++;
	}
}

void	draw_minimap(t_app *papp, t_image img)
{
	t_coor	i;

	i.y = 0;
	while (i.y < array_size(papp->map))
	{
		i.x = 0;
		while (i.x < lp_strlen(papp->map[(int)i.y]))
		{
			if (papp->map[(int)i.y][(int)i.x] == '1')
				draw_rect(img, (t_coor){i.x * papp->tile_w + 10,
					i.y * papp->tile_h + 10},
					(t_coor){papp->tile_w, papp->tile_h}, 0xFFFFFF);
			if (papp->map[(int)i.y][(int)i.x] == '0')
				draw_rect(img, (t_coor){i.x * papp->tile_w + 10,
					i.y * papp->tile_h + 10},
					(t_coor){papp->tile_w, papp->tile_h}, 0x666666);
			i.x++;
		}
		i.y++;
	}
	draw_rays(papp, img);
	draw_rect(img,
		(t_coor){papp->p.x * papp->tile_w - papp->tile_w * MOVE_STEP / 2 + 10,
		papp->p.y * papp->tile_h - papp->tile_h * MOVE_STEP / 2 + 10},
		(t_coor){papp->tile_w * MOVE_STEP, papp->tile_h * MOVE_STEP}, 0xFFFF);
}
