/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:07:10 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/12 03:35:41 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_coor	rad_to_vect(float angle)
{
	return ((t_coor){cosf(angle), sinf(angle)});
}

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

t_ray	get_first_wall(char **map, t_coor o, t_coor v)
{
	t_coor			side_dist;
	const t_coor	step = (t_coor){1.0 + (v.x < 0) * -2, 1.0 + (v.y < 0) * -2};
	const t_coor	dlt = get_delta(v);

	side_dist = (t_coor){((int)o.x + 1.0 - o.x) * dlt.x, ((int)o.y + 1.0 - o.y) * dlt.y};
	if (v.x < 0)
		side_dist.x = (o.x - (int)o.x) * dlt.x;
	if (v.y < 0)
		side_dist.y = (o.y - (int)o.y) * dlt.y;
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += dlt.x;
			o.x += step.x;
			if (map[(int)o.y][(int)o.x] == '1')
				return ((t_ray){o.x, o.y, side_dist.x - dlt.x, 1});
			continue ;
		}
		side_dist.y += dlt.y;
		o.y += step.y;
		if (map[(int)o.y][(int)o.x] == '1')
			return ((t_ray){o.x, o.y, side_dist.y - dlt.y, 0});
	}
}

void	draw_line(t_image win_image, t_coor s, t_coor e, int c)
{
	const t_coor	d
		= (t_coor){abs((int)e.x - (int)s.x), abs((int)e.y - (int)s.y)};
	const t_coor	step
		= (t_coor){-1 + (s.x < e.x) * 2, -1 + (s.y < e.y) * 2};
	int				err;
	int				e2;

	err = d.x - d.y;
	while (1)
	{
		image_put_px(win_image, s.x, s.y, c);
		if (s.x == e.x && s.y == e.y)
			break ;
		e2 = 2 * err;
		if (e2 > -d.y)
		{
			err -= d.y;
			s.x += step.x;
		}
		if (e2 < d.x)
		{
			err += d.x;
			s.y += step.y;
		}
	}
}
