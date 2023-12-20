/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/20 12:34:20 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	get_tex_x(t_app *papp, t_wall ray, t_texture tex)
{
	if (ray.is_vertical)
	{
		if (papp->p.x > ray.impact.x)
			return ((1 - ray.impact.y + (int)ray.wall.y) * (double)tex.w);
		return ((ray.impact.y - (int)ray.wall.y) * (double)tex.w);
	}
	else
	{
		if (papp->p.y < ray.impact.y)
			return ((1 - ray.impact.x + (int)ray.wall.x) * (double)tex.w);
		return ((ray.impact.x - (int)ray.wall.x) * (double)tex.w);
	}
}

t_texture	get_texture(t_app *papp, t_wall ray)
{
	if (ray.is_vertical)
	{
		if (papp->p.x > ray.impact.x)
			return (papp->texwe);
		else
			return (papp->texea);
	}
	else
	{
		if (papp->p.y > ray.impact.y)
			return (papp->texno);
		else
			return (papp->texso);
	}
}

void	draw_wall(t_app *papp, t_image img, size_t ray_start, size_t ray_end)
{
	const t_texture	tex = get_texture(papp, papp->rays[ray_start]);
	long			wall_h;
	t_xy			i;
	double			ratio_y;
	size_t			tex_x;

	i.x = ray_start;
	while (i.x < ray_end)
	{
		wall_h = WIN_H
			/ (papp->rays[(int)i.x].len + (!papp->rays[(int)i.x].len));
		ratio_y = (double)tex.h / wall_h;
		tex_x = get_tex_x(papp, papp->rays[(int)i.x], tex);
		i.y = -1;
		while (++i.y < wall_h)
		{
			image_put_px(img, i.x, i.y + WIN_H * 0.5 - wall_h * 0.5,
				tex_get_px_color(tex, tex_x, i.y * ratio_y));
		}
		i.x++;
	}
}

void	draw_walls(t_app *papp, t_image img)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (i < array_size(papp->rays))
	{
		j = i;
		while (j < array_size(papp->rays)
			&& (int)papp->rays[i].wall.x == (int)papp->rays[j].wall.x
			&& (int)papp->rays[i].wall.y == (int)papp->rays[j].wall.y
			&& papp->rays[i].is_vertical == papp->rays[j].is_vertical)
			j++;
		draw_wall(papp, img, i, j);
		i = j;
	}
}
