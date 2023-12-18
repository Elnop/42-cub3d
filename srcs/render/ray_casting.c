/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:40:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/18 15:13:53 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>
#include <stdlib.h>

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

t_coo	set_deltas(t_coo v)
{
	t_coo	delta;

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

t_coo	set_side_dists(t_coo origin, t_coo dir, t_coo delta)
{
	t_coo	side_dist;

	side_dist = (t_coo){((int)origin.x + 1 - origin.x) * delta.x,
		((int)origin.y + 1 - origin.y) * delta.y};
	if (dir.x < 0)
		side_dist.x = (origin.x - (int)origin.x) * delta.x;
	if (dir.y < 0)
		side_dist.y = (origin.y - (int)origin.y) * delta.y;
	return (side_dist);
}

t_coo	*get_wall_line(t_coo player, t_coo w, int side)
{
	t_coo	*wall_limits;

	wall_limits = malloc(2 * sizeof(t_coo));
	if (side)
	{
		if (player.x > (int)w.x)
		{
			wall_limits[0] = (t_coo){(int)w.x + 1, (int)w.y};
			wall_limits[1] = (t_coo){(int)w.x + 1, (int)w.y + 1};
			return (wall_limits);
		}
		wall_limits[0] = (t_coo){(int)w.x, (int)w.y};
		wall_limits[1] = (t_coo){(int)w.x, (int)w.y + 1};
		return (wall_limits);
	}
	if (player.y > (int)w.y)
	{
		wall_limits[0] = (t_coo){(int)w.x, (int)w.y + 1};
		wall_limits[1] = (t_coo){(int)w.x + 1, (int)w.y + 1};
		return (wall_limits);
	}
		wall_limits[0] = (t_coo){(int)w.x, (int)w.y};
		wall_limits[1] = (t_coo){(int)w.x + 1, (int)w.y};
	return (wall_limits);
}

t_ray	set_ray(t_app *papp, t_coo wall, double angle, int side)
{
	const t_coo		*wall_line = get_wall_line(papp->p, wall, side);
	const t_coo		w = lines_intersection(papp->p,
			(t_coo){papp->p.x + cos(angle), papp->p.y + sin(angle)},
			wall_line[0], wall_line[1]);
	printf("player: [%f, %f]\n", papp->p.x, papp->p.y);
	printf("wall limits: [%f, %f] [%f, %f]\n", wall_line[0].x, wall_line[0].y, wall_line[1].x, wall_line[1].y);
	printf("wall: [%f, %f]\n", w.x, w.y);
	const t_coo	plane = rad_to_vect(papp->p_dir + M_PI / 2);
	const t_coo		plane_start = lines_intersection((t_coo){papp->p.x + plane.x, papp->p.y + plane.y},
			papp->p, w, (t_coo){w.x + cos(papp->p_dir),
			w.y + sin(papp->p_dir)});
	const double	dist = sqrt(pow(plane_start.x - w.x, 2)
			+ pow(plane_start.y - w.y, 2));
	return ((t_ray){w.x, w.y, plane_start.x, plane_start.y, dist, angle, side});
}

t_ray	get_first_wall(t_app *papp, t_coo origin, double angle)
{
	const t_coo	dir = rad_to_vect(angle);
	t_coo			side_dists;
	const t_coo	step = (t_coo){1 + (dir.x < 0) * -2, 1 + (dir.y < 0) * -2};
	const t_coo	delta = set_deltas(dir);
	t_coo			curr;

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
