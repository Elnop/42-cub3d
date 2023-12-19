/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:07:10 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/18 19:17:48 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_xy	rad_to_vect(double angle)
{
	return ((t_xy){cos(angle), sin(angle)});
}

t_xy	lines_intersection(t_xy p1, t_xy p2, t_xy p3, t_xy p4)
{
	return ((t_xy){
		((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x)
			- (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x))
		/ ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x)),
		((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y)
			- (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x))
		/ ((p1.x - p2.x) * (p3.y - p4.y)  - (p1.y - p2.y) * (p3.x - p4.x))
	});
}

void	draw_line(t_image win_image, t_xy s, t_xy e, int c)
{
	const t_xy	d
		= (t_xy){abs((int)e.x - (int)s.x), abs((int)e.y - (int)s.y)};
	const t_xy	step
		= (t_xy){-1 + (s.x < e.x) * 2, -1 + (s.y < e.y) * 2};
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
