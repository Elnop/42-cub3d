/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 00:26:30 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/30 17:21:07 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
}
