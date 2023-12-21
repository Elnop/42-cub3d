/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:22:10 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/21 15:36:53 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	hooks_update(t_app *papp)
{
	if (papp->hooks.w)
		go_front(papp);
	if (papp->hooks.s)
		go_back(papp);
	if (papp->hooks.d)
		go_right(papp);
	if (papp->hooks.a)
		go_left(papp);
	if (papp->hooks.left)
	{
		papp->p_dir -= 2 * M_PI * ROTATE_STEP;
		if (papp->p_dir < -M_PI)
			papp->p_dir += 2 * M_PI;
	}
	if (papp->hooks.right)
	{
		papp->p_dir += 2 * M_PI * ROTATE_STEP;
		if (papp->p_dir > M_PI)
			papp->p_dir -= 2 * M_PI;
	}
}