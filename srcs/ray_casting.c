/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:40:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/15 01:08:46 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_coor	get_delta(t_coor v)
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

t_ray	get_first_wall(char **map, t_coor o, double angle)
{
	const t_coor	v = rad_to_vect(angle);
	t_coor			sd;
	const t_coor	step = (t_coor){1 + (v.x < 0) * -2, 1 + (v.y < 0) * -2};
	const t_coor	dl = get_delta(v);

	sd = (t_coor){((int)o.x + 1 - o.x) * dl.x, ((int)o.y + 1 - o.y) * dl.y};
	if (v.x < 0)
		sd.x = (o.x - (int)o.x) * dl.x;
	if (v.y < 0)
		sd.y = (o.y - (int)o.y) * dl.y;
	while (1)
	{
		if (sd.x < sd.y)
		{
			sd.x += dl.x;
			o.x += step.x;
			if (map[(int)o.y][(int)o.x] == '1')
				return ((t_ray){o.x, o.y, sd.x - dl.x, angle, 1});
			continue ;
		}
		sd.y += dl.y;
		o.y += step.y;
		if (map[(int)o.y][(int)o.x] == '1')
			return ((t_ray){o.x, o.y, sd.y - dl.y, angle, 0});
	}
}
