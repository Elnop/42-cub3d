/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:07:10 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/18 14:39:43 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_coo	rad_to_vect(double angle)
{
	return ((t_coo){cos(angle), sin(angle)});
}

t_coo	lines_intersection(t_coo p1, t_coo p2, t_coo p3, t_coo p4)
{
	return ((t_coo){
		((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x)
			- (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x))
		/ ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x)),
		((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y)
			- (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x))
		/ ((p1.x - p2.x) * (p3.y - p4.y)  - (p1.y - p2.y) * (p3.x - p4.x))
	});
}

void	draw_line(t_image win_image, t_coo s, t_coo e, int c)
{
	const t_coo	d
		= (t_coo){abs((int)e.x - (int)s.x), abs((int)e.y - (int)s.y)};
	const t_coo	step
		= (t_coo){-1 + (s.x < e.x) * 2, -1 + (s.y < e.y) * 2};
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
