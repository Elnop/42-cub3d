/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 00:26:30 by lperroti          #+#    #+#             */
/*   Updated: 2023/11/30 22:01:58 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stddef.h>

void	draw_line(t_image win_image, size_t x0, size_t y0, size_t x1, size_t y1, int color)
{
	bool	steep = false; 
	if (x0-x1 < y0-y1) {
		lp_memswap(&x0, &y0, sizeof(size_t));
		lp_memswap(&x1, &y1, sizeof(size_t));
        steep = true; 
    } 
    if (x0>x1) { 
        lp_memswap(&x0, &x1, sizeof(size_t)); 
        lp_memswap(&y0, &y1, sizeof(size_t)); 
    } 
    size_t dx = x1-x0;
    size_t dy = y1-y0;
    float derror = dy/(float)dx;
    float error = 0;
    size_t y = y0;
    for (size_t x=x0; x<=x1; x++) {
        if (steep) { 
            image_put_px(win_image, y, x, color);
        } else { 
            image_put_px(win_image, x, y, color);

        } 
        error += derror; 
        if (error>.5) { 
            y += (y1>y0?1:-1); 
            error -= 1.; 
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
	draw_line(win_image, ceil(papp->player.x * papp->mini_map_tile_w + papp->mini_map_tile_w / 2) + 10, ceil(papp->player.y * papp->mini_map_tile_h + papp->mini_map_tile_h / 2) + 10, ceil(papp->player.x * papp->mini_map_tile_w + papp->mini_map_tile_w / 2) + 10, 10 + papp->mini_map_tile_h, 0xFF);
}
