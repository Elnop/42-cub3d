/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:07:10 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/17 05:41:40 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_coor	rad_to_vect(double angle)
{
	return ((t_coor){cos(angle), sin(angle)});
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
