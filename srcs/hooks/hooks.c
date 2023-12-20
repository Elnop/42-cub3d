/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:33:46 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/19 04:59:56 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	hooks_handler(int kc, t_app *papp)
{
	if (kc == XK_Escape)
		destroy_and_exit(papp);
	if (kc == XK_w)
		go_front(papp);
	if (kc == XK_s)
		go_back(papp);
	if (kc == XK_d)
		go_right(papp);
	if (kc == XK_a)
		go_left(papp);
	if (kc == XK_Left)
	{
		papp->p_dir -= 2 * M_PI * ROTATE_STEP;
		if (papp->p_dir < -M_PI)
			papp->p_dir += 2 * M_PI;
	}
	if (kc == XK_Right)
	{
		papp->p_dir += 2 * M_PI * ROTATE_STEP;
		if (papp->p_dir > M_PI)
			papp->p_dir -= 2 * M_PI;
	}
	return (1);
}

void	init_hooks(t_app *papp)
{
	mlx_hook(papp->win, 2, 1L, hooks_handler, papp);
	mlx_hook(papp->win, 17, 0, destroy_and_exit, papp);
}