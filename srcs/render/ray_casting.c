/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:40:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/20 11:01:55 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>
#include <stdlib.h>

t_xy	set_deltas(t_xy v)
{
	t_xy	delta;

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

t_xy	set_side_dists(t_xy origin, t_xy dir, t_xy delta)
{
	t_xy	side_dist;

	side_dist = (t_xy){((int)origin.x + 1 - origin.x) * delta.x,
		((int)origin.y + 1 - origin.y) * delta.y};
	if (dir.x < 0)
		side_dist.x = (origin.x - (int)origin.x) * delta.x;
	if (dir.y < 0)
		side_dist.y = (origin.y - (int)origin.y) * delta.y;
	return (side_dist);
}

t_ray	set_ray(t_app *papp, t_xy wall, double angle, int is_vert)
{
	const t_xy	cam_vec = rad_to_vect(papp->p_dir + M_PI / 2);
	t_xy		cam_p;
	t_xy		*wall_line;
	double		dist;
	t_xy		impact;

	wall_line = get_wall_limits(papp->p, wall, is_vert);
	impact = lines_intersection(papp->p,
			(t_xy){papp->p.x + cos(angle), papp->p.y + sin(angle)},
			wall_line[0], wall_line[1]);
	cam_p = lines_intersection(
			(t_xy){papp->p.x + cam_vec.x, papp->p.y + cam_vec.y},
			papp->p, impact,
			(t_xy){impact.x + cos(papp->p_dir), impact.y + sin(papp->p_dir)});
	dist = sqrt(pow(cam_p.x - impact.x, 2) + pow(cam_p.y - impact.y, 2));
	free(wall_line);
	return ((t_ray){wall, impact, cam_p, dist, angle, is_vert});
}

t_ray	dda(t_app *papp, t_xy origin, double angle)
{
	const t_xy	dir = rad_to_vect(angle);
	const t_xy	step = (t_xy){1 + (dir.x < 0) * -2, 1 + (dir.y < 0) * -2};
	const t_xy	delta = set_deltas(dir);
	t_xy		side_dists;
	t_xy		curr;

	curr = origin;
	side_dists = set_side_dists(origin, dir, delta);
	while (1)
	{
		if (side_dists.x < side_dists.y)
		{
			side_dists.x += delta.x;
			curr.x += step.x;
			if (papp->map[(int)curr.y][(int)curr.x] == '1')
				return (set_ray(papp, curr, angle, 1));
			continue ;
		}
		side_dists.y += delta.y;
		curr.y += step.y;
		if (papp->map[(int)curr.y][(int)curr.x] == '1')
			return (set_ray(papp, curr, angle, 0));
	}
}

t_array	get_walls(t_app *papp)
{
	t_array			rays;
	double			angle;

	rays = array_new(WIN_W, sizeof(t_ray), NULL, NULL);
	angle = papp->p_dir -(FOV * M_PI) / 2;
	while (angle - papp->p_dir <= (FOV * M_PI) / 2)
	{
		array_pushback(&rays,
			(t_ray []){dda(papp, papp->p,
				angle)});
		angle += (FOV * M_PI) / WIN_W;
	}
	return (rays);
}
