/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:07:10 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/11 20:19:58 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_coor	rad_to_vect(float angle)
{
	return ((t_coor){cosf(angle), sinf(angle)});
}

t_ray_impact	get_first_wall(char **map, t_coor o, t_coor v)
{
	t_coor			side_dist;
	const t_coor	step = (t_coor){1 + (v.x < 0) * -2, 1 + (v.y < 0) * -2};
	const t_coor	dlt = (t_coor){
		fabs(1 / v.x + (!v.x) * 1e30), fabs(1 / v.y + (!v.y) * 1e30)};

	side_dist = (t_coor){(o.x + 1 - o.x) * dlt.x, (o.y + 1 - o.y) * dlt.y};
	if (v.x < 0)
		side_dist.x = (o.x - o.x) * dlt.x;
	if (v.y < 0)
		side_dist.y = (o.y - o.y) * dlt.y;
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += dlt.x;
			o.x += step.x;
			if (map[(int)o.y][(int)o.x] == '1')
				return ((t_ray_impact){o.x, o.y, side_dist.x - dlt.x, 1});
			continue ;
		}
		side_dist.y += dlt.y;
		o.y += step.y;
		if (map[(int)o.y][(int)o.x] == '1')
			return ((t_ray_impact){o.x, o.y, side_dist.y - dlt.y, 0});
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
