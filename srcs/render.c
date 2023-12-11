/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/11 22:09:29 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_walls(t_app *papp, t_image img)
{
	t_ray_impact	wall;
	float			angle;
	int				ray_i;
	int				wall_height;
	int				wall_start;

	ray_i = 0;
	angle = -(FOV * M_PI) / 2 + papp->p_dir;
	while (angle < (FOV * M_PI) / 2 + papp->p_dir)
	{
		wall = get_first_wall(papp->map, papp->p, rad_to_vect(angle));
		wall_height = WIN_HEIGHT / (wall.dist + (!wall.dist) * 1);
		wall_start = WIN_HEIGHT / 2 - wall_height / 2;
		draw_line(img, (t_coor){ray_i, wall_start},
			(t_coor){ray_i, wall_start + wall_height}, 0xFF00FF);
		angle += (FOV * M_PI) / WIN_WIDTH;
		ray_i++;
	}
}
