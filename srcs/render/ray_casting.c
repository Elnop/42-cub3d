/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:40:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/17 05:57:09 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_array	ray_cast(t_app *papp)
{
	t_array			rays;
	double			angle;

	rays = array_new(WIN_W, sizeof(t_ray), NULL, NULL);
	angle = papp->p_dir -(FOV * M_PI) / 2;
	while (angle - papp->p_dir <= (FOV * M_PI) / 2)
	{
		array_pushback(&rays,
			(t_ray []){get_first_wall(papp, papp->p,
				angle)});
		angle += (FOV * M_PI) / WIN_W;
	}
	return (rays);
}

t_coor	set_deltas(t_coor v)
{
	t_coor	delta;

	if (!v.x)
		delta.x = 1e30;
	else
		delta.x = fabs(1 / v.x);
	if (!v.y)
		delta.y = 1e30;
	else
		delta.y = fabs(1 / v.y);
	return (delta);
}

t_coor	set_side_dists(t_coor origin, t_coor dir, t_coor delta)
{
	t_coor	side_dist;

	side_dist = (t_coor){((int)origin.x + 1 - origin.x) * delta.x,
		((int)origin.y + 1 - origin.y) * delta.y};
	if (dir.x < 0)
		side_dist.x = (origin.x - (int)origin.x) * delta.x;
	if (dir.y < 0)
		side_dist.y = (origin.y - (int)origin.y) * delta.y;
	return (side_dist);
}

t_ray	get_first_wall(t_app *papp, t_coor origin, double angle)
{
	const t_coor	dir = rad_to_vect(angle);
	t_coor			side_dists;
	const t_coor	step = (t_coor){1 + (dir.x < 0) * -2, 1 + (dir.y < 0) * -2};
	const t_coor	delta = set_deltas(dir);
	t_coor			curr;

	curr = origin;
	side_dists = set_side_dists(origin, dir, delta);
	while (1)
	{
		if (side_dists.x < side_dists.y)
		{
			side_dists.x += delta.x;
			curr.x += step.x;
			if (papp->map[(int)curr.y][(int)curr.x] == '1')
				return ((t_ray){curr.x, curr.y, origin.x, origin.y,
					side_dists.x - delta.x, angle, 1});
			continue ;
		}
		side_dists.y += delta.y;
		curr.y += step.y;
		if (papp->map[(int)curr.y][(int)curr.x] == '1')
		{
			return ((t_ray){curr.x, curr.y, origin.x, origin.y,
				side_dists.y - delta.y, angle, 0});
		}
	}
}
