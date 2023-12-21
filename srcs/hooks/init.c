/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:33:46 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/21 15:31:06 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <X11/X.h>

static int	press_handler(int keydata, t_app *papp)
{
	if (keydata == XK_Escape)
		destroy_and_exit(papp);
	if (keydata == XK_w)
		papp->hooks.w = true;
	if (keydata == XK_s)
		papp->hooks.s = true;
	if (keydata == XK_d)
		papp->hooks.d = true;
	if (keydata == XK_a)
		papp->hooks.a = true;
	if (keydata == XK_Left)
		papp->hooks.left = true;
	if (keydata == XK_Right)
		papp->hooks.right = true;
	return (1);
}

static int	release_handler(int keydata, t_app *papp)
{
	if (keydata == XK_w)
		papp->hooks.w = false;
	if (keydata == XK_s)
		papp->hooks.s = false;
	if (keydata == XK_d)
		papp->hooks.d = false;
	if (keydata == XK_a)
		papp->hooks.a = false;
	if (keydata == XK_Left)
		papp->hooks.left = false;
	if (keydata == XK_Right)
		papp->hooks.right = false;
	return (1);
}

void	init_hooks(t_app *papp)
{
	mlx_hook(papp->win, KeyPress, KeyPressMask, press_handler, papp);
	mlx_hook(papp->win, KeyRelease, KeyReleaseMask, release_handler, papp);
	mlx_hook(papp->win, 17, 0, destroy_and_exit, papp);
}
