/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:48:03 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/18 13:54:20 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	can_go(t_app *papp, t_coo n)
{
	if (n.y <= 0 || n.y <= 0 || n.y >= array_size(papp->map)
		|| n.x >= lp_strlen(((char **)papp->map)[(int)n.y])
		|| papp->map[(int)n.y][(int)n.x] == '1'
		|| papp->map[(int)(n.y - MOVE_STEP * 0.5)][(int)n.x] == '1')
		return (false);
	return (true);
}

void	go_front(t_app *papp)
{
	t_coo	next;

	next = (t_coo){papp->p.x + (double)MOVE_STEP * cos(papp->p_dir),
		papp->p.y + MOVE_STEP * sin(papp->p_dir)};
	if (can_go(papp, next))
		papp->p = next;
}

void	go_back(t_app *papp)
{
	t_coo	next;

	next = (t_coo){papp->p.x - MOVE_STEP * cos(papp->p_dir),
		papp->p.y - MOVE_STEP * sin(papp->p_dir)};
	if (can_go(papp, next))
		papp->p = next;
}

void	go_left(t_app *papp)
{
	t_coo	next;

	next = (t_coo){papp->p.x + MOVE_STEP * sin(papp->p_dir),
		papp->p.y - MOVE_STEP * cos(papp->p_dir)};
	if (can_go(papp, next))
		papp->p = next;
}

void	go_right(t_app *papp)
{
	t_coo	next;

	next = (t_coo){papp->p.x - MOVE_STEP * sin(papp->p_dir),
		papp->p.y + MOVE_STEP * cos(papp->p_dir)};
	if (can_go(papp, next))
		papp->p = next;
}
