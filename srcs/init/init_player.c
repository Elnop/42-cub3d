/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:35:40 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/17 04:05:38 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	set_player(t_app *papp, double x, double y, char cardinal)
{
	papp->map[(int)y][(int)x] = '0';
	papp->p.x = x + 0.5;
	papp->p.y = y + 0.5;
	if (cardinal == 'N')
		papp->p_dir = -M_PI / 2;
	if (cardinal == 'S')
		papp->p_dir = M_PI / 2;
	if (cardinal == 'E')
		papp->p_dir = 0;
	if (cardinal == 'W')
		papp->p_dir = -M_PI;
	return (!init_player(papp));
}

bool	init_player(t_app *papp)
{
	double	y;

	y = 0;
	while (y < array_size(papp->map))
	{
		if (lp_strchr(papp->map[(int)y], 'N'))
			return (set_player(papp,
					lp_strchr(papp->map[(int)y], 'N')
					- papp->map[(int)y], y, 'N'));
		if (lp_strchr(papp->map[(int)y], 'O'))
			return (set_player(papp,
					lp_strchr(papp->map[(int)y], 'O')
					- papp->map[(int)y], y, 'O'));
		if (lp_strchr(papp->map[(int)y], 'W'))
			return (set_player(papp,
					lp_strchr(papp->map[(int)y], 'W')
					- papp->map[(int)y], y, 'W'));
		if (lp_strchr(papp->map[(int)y], 'S'))
			return (set_player(papp,
					lp_strchr(papp->map[(int)y], 'S')
					- papp->map[(int)y], y, 'S'));
		y++;
	}
	return (false);
}
