/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/18 15:09:07 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_texture	get_texture(t_app *papp, t_ray ray)
{
	if (ray.ray_mod)
	{
		if (papp->p.x > ray.wx)
			return (papp->texwe);
		else
			return (papp->texea);
	}
	else
	{
		if (papp->p.y > ray.wy)
			return (papp->texno);
		else
			return (papp->texso);
	}
}

void	draw_wall(t_app *papp, t_ray *rays, size_t *i, t_image img)
{
	t_coo		pos;
	t_coo		s;
	t_texture	t;
	size_t		end_wall;
	long		wall_h;

	t = get_texture(papp, rays[*i]);
	end_wall = *i;
	while (end_wall < array_size(rays) && (int)rays[*i].wx == (int)rays[end_wall].wx
		&& (int)rays[*i].wy == (int)rays[end_wall].wy
		&& rays[*i].ray_mod == rays[end_wall].ray_mod)
		end_wall++;
	pos.x = *i - 1;
	while (pos.x < end_wall)
	{
		if (!rays[(int)pos.x].ray_mod)
			wall_h = WIN_H / (rays[(int)pos.x].dist + (!rays[(int)pos.x].dist));
		else
			wall_h = WIN_H / (rays[(int)pos.x].dist + (!rays[(int)pos.x].dist));
		s = (t_coo){(double)t.w / (end_wall - *i), (double)t.h / wall_h};
		pos.y = -1;
		while (++pos.y < wall_h)
			image_put_px(img, pos.x, pos.y + WIN_H * 0.5 - wall_h * 0.5,
				image_get_px_color(t.img, (pos.x - *i + 1) * s.x, pos.y * s.y));
		pos.x++;
	}
	*i = pos.x;
}

void	draw_walls(t_app *papp, t_image img)
{
	size_t	i;
	t_array	rays;

	rays = ray_cast(papp);
	i = 0;
	while (i < array_size(rays))
	{
		draw_wall(papp, rays, &i, img);
		i++;
	}
	array_free(rays);
}
