/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:33:46 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/03 02:50:54 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	hooks_handler(int kc, t_app *papp)
{
	if (kc == XK_Escape)
		destroy_and_exit(papp);
	if (kc == XK_w
		&& ((char **)papp->map)[(int)floor(papp->player.y - MOVE_STEP)][(int)floor(papp->player.x)] == '0')
		papp->player.y -= MOVE_STEP;
	if (kc == XK_s
		&& ((char **)papp->map)[(int)ceil(papp->player.y + MOVE_STEP)][(int)ceil(papp->player.x)] == '0')
		papp->player.y += MOVE_STEP;
	if (kc == XK_d
		&& ((char **)papp->map)[(int)ceil(papp->player.y)][(int)ceil(papp->player.x + MOVE_STEP)] == '0')
		papp->player.x += MOVE_STEP;
	if (kc == XK_a
		&& ((char **)papp->map)[(int)floor(papp->player.y)][(int)floor(papp->player.x - MOVE_STEP)] == '0')
		papp->player.x -= MOVE_STEP;
	if (kc == XK_Right)
	{
		papp->player_dir -= 2 * M_PI * ROTATE_STEP;
		if (papp->player_dir < -M_PI)
			papp->player_dir += 2 * M_PI;
	}
	if (kc == XK_Left)
	{
		papp->player_dir += 2 * M_PI * ROTATE_STEP;
		if (papp->player_dir > M_PI)
			papp->player_dir -= 2 * M_PI;
	}
	return (1);
}

void	init_hooks(t_app *papp)
{
	mlx_hook(papp->win, 2, 1L << 0, hooks_handler, papp);
	mlx_hook(papp->win, 17, 0, destroy_and_exit, papp);
}
