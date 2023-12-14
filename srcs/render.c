/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/14 03:01:43 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stddef.h>

t_array	ray_cast(t_app *papp)
{
	t_array			rays;
	float			angle;
	long			ray_i;

	ray_i = 0;
	angle = -(FOV * M_PI) / 2 + papp->p_dir;
	rays = array_new(WIN_W, sizeof(t_ray), NULL, NULL);
	while (angle < (FOV * M_PI) / 2 + papp->p_dir)
	{
		array_pushback(&rays,
			(t_ray []){get_first_wall(papp->map, papp->p,
				rad_to_vect(angle))});
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

void	draw_wall(t_app *papp, t_array rays, size_t *win_index, t_image img)
{
	size_t		end_wall;
	double		stepx;
	double		stepy;
	t_texture	tex;
	long		wall_h;
	long		wall_start;
	long		y;
	size_t		x;

	tex = get_texture(papp, ((t_ray *)rays)[*win_index]);
	end_wall = *win_index;
	while (end_wall < array_size(rays)
		&& ((t_ray *)rays)[*win_index].x == ((t_ray *)rays)[end_wall].x
		&& ((t_ray *)rays)[*win_index].y == ((t_ray *)rays)[end_wall].y)
		end_wall++;
	x = *win_index;
	while (x < end_wall)
	{
		wall_h = WIN_H / (((t_ray *)rays)[x].dist + (!((t_ray *)rays)[x].dist));
		wall_start = WIN_H / 2 - wall_h / 2;
		stepx = (double)tex.width / (double)(end_wall - *win_index);
		stepy = (double)tex.height / (double)wall_h;
		y = 0;
		while (y < wall_h)
		{
			image_put_px(img, x, y + wall_start,
				image_get_px_color(tex.img, floor( (x - *win_index) * stepx), floor((double)y * stepy)));
			y++;
		}
		x++;
	}
	*win_index = x;
}

void	draw_walls(t_app *papp, t_image img)
{
	size_t	i;
	t_array	rays;

	rays = ray_cast(papp);
	i = 0;
	while (i < array_size(rays))
	{
		//printf("x: %f y: %f dist: %f ray_mod: %d\n", ((t_ray *)rays)[i].x, ((t_ray *)rays)[i].y, ((t_ray *)rays)[i].dist, ((t_ray *)rays)[i].ray_mod);
		draw_wall(papp, rays, &i, img);
		i++;
	}
	array_free(rays);
}
