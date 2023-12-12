/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/12 03:55:57 by lperroti         ###   ########.fr       */
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
	rays = array_new(WIN_WIDTH, sizeof(t_ray), NULL, NULL);
	while (angle < (FOV * M_PI) / 2 + papp->p_dir)
	{
		array_pushback(&rays,
			(t_ray []){get_first_wall(papp->map, papp->p,
				rad_to_vect(angle))});
		angle += (FOV * M_PI) / WIN_WIDTH;
		ray_i++;
	}
	return (rays);
}

void	draw_walls(t_app *papp, t_image img)
{
	size_t	i;
	t_array	rays;
	long	wall_h;
	long	wall_start;
	int 	color;

	rays = ray_cast(papp);
	i = 0;
	while (i < array_size(rays))
	{
		printf("x: %f y: %f dist: %f ray_mod: %d\n", ((t_ray *)rays)[i].x, ((t_ray *)rays)[i].y, ((t_ray *)rays)[i].dist, ((t_ray *)rays)[i].ray_mod);
		wall_h = WIN_H / (((t_ray *)rays)[i].dist + (!((t_ray *)rays)[i].dist));
		wall_start = WIN_H / 2 - wall_h / 2;
		if (((t_ray *)rays)[i].ray_mod)
		{
			if (papp->p.x > ((t_ray *)rays)[i].x)
				color = 0xf4141c;
			else
				color = 0xffc0cb;
		}
		else
		{
			if (papp->p.y > ((t_ray *)rays)[i].y)
				color = 0x1c1c84;
			else
				color = 0x11f3af;
		}
		draw_line(img, (t_coor){i, wall_start},
			(t_coor){i, wall_start + wall_h}, color);
		i++;
	}
	printf("rays_count: %lu\n\n", array_size(rays));
	array_free(rays);
}