/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/15 01:08:46 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_array	ray_cast(t_app *papp)
{
	t_array			rays;
	double			angle;
	long			ray_i;

	ray_i = 0;
	angle = -(FOV * M_PI) / 2 + papp->p_dir;
	rays = array_new(WIN_W, sizeof(t_ray), NULL, NULL);
	while (angle < (FOV * M_PI) / 2 + papp->p_dir)
	{
		array_pushback(&rays,
			(t_ray []){get_first_wall(papp->map, papp->p,
				angle)});
		angle += (FOV * M_PI) / WIN_W;
		ray_i++;
	}
	return (rays);
}

t_texture	get_texture(t_app *papp, t_ray ray)
{
	if (ray.ray_mod)
	{
		if (papp->p.x > ray.x)
			return (papp->texwe);
		else
			return (papp->texea);
	}
	else
	{
		if (papp->p.y > ray.y)
			return (papp->texno);
		else
			return (papp->texso);
	}
}

void	draw_wall(t_app *papp, t_ray *rays, size_t *wi, t_image img)
{
	t_coor		pos;
	t_coor		s;
	t_texture	t;
	size_t		end_wall;
	long		wall_h;

	t = get_texture(papp, rays[*wi]);
	end_wall = *wi;
	while (end_wall < array_size(rays) && rays[*wi].x == rays[end_wall].x
		&& rays[*wi].y == rays[end_wall].y
		&& rays[*wi].ray_mod == rays[end_wall].ray_mod)
		end_wall++;
	pos.x = *wi;
	while (pos.x < end_wall)
	{
		wall_h = WIN_H / (rays[(int)pos.x].dist + (rays[(int)pos.x].dist <= 0));
		s = (t_coor){(double)t.w / (end_wall - *wi), (double)t.h / wall_h};
		pos.y = -1;
		while (++pos.y < wall_h)
			image_put_px(img, pos.x, pos.y + WIN_H * 0.5 - wall_h * 0.5,
				image_get_px_color(t.img, (pos.x - *wi) * s.x, pos.y * s.y));
		pos.x++;
	}
	*wi = pos.x;
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
