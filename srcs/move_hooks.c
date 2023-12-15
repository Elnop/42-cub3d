/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:48:03 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/15 00:42:00 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	go_front(t_app *papp)
{
	t_coor	next;

	next = (t_coor){papp->p.x + (double)MOVE_STEP * cos(papp->p_dir),
		papp->p.y + MOVE_STEP * sin(papp->p_dir)};
	if (next.y <= 0 || next.y <= 0 || next.y >= array_size(papp->map)
		|| next.x >= lp_strlen(((char **)papp->map)[(int)next.y])
		|| ((char **)papp->map)[(int)next.y][(int)next.x] == '1')
		return ;
	papp->p = next;
}

void	go_back(t_app *papp)
{
	t_coor	next;

	next = (t_coor){papp->p.x - MOVE_STEP * cos(papp->p_dir),
		papp->p.y - MOVE_STEP * sin(papp->p_dir)};
	if (next.y <= 0 || next.y <= 0 || next.y >= array_size(papp->map)
		|| next.x >= lp_strlen(((char **)papp->map)[(int)next.y])
		|| ((char **)papp->map)[(int)next.y][(int)next.x] == '1')
		return ;
	papp->p = next;
}

void	go_left(t_app *papp)
{
	t_coor	next;

	next = (t_coor){papp->p.x + MOVE_STEP * sin(papp->p_dir),
		papp->p.y - MOVE_STEP * cos(papp->p_dir)};
	if (next.y <= 0 || next.y <= 0 || next.y >= array_size(papp->map)
		|| next.x >= lp_strlen(((char **)papp->map)[(int)next.y])
		|| ((char **)papp->map)[(int)next.y][(int)next.x] == '1')
		return ;
	papp->p = next;
}

void	go_right(t_app *papp)
{
	t_coor	next;

	next = (t_coor){papp->p.x - MOVE_STEP * sin(papp->p_dir),
		papp->p.y + MOVE_STEP * cos(papp->p_dir)};
	if (next.y <= 0 || next.y <= 0 || next.y >= array_size(papp->map)
		|| next.x >= lp_strlen(((char **)papp->map)[(int)next.y])
		|| ((char **)papp->map)[(int)next.y][(int)next.x] == '1')
		return ;
	papp->p = next;
}
