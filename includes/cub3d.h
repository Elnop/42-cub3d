/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:01:40 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/04 04:06:20 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stddef.h>
# define XK_MISCELLANY
# define XK_LATIN1
# include "../libs/minilibx-linux/mlx.h"
# include <X11/keysymdef.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../libs/liblp_c/liblp.h"

# define WIN_HEIGHT 700
# define WIN_WIDTH 1200
# define MAP_SIZE 0.3
# define MOVE_STEP 1
# define ROTATE_STEP 0.0625
# define FOV 0.25 // FRACTION OF 360

# define HELPER "./cub3d <map file>\n"

typedef struct s_coordinates {
	float	x;
	float	y;
}	t_coordinates;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef union s_color {
	int	hex;
	struct
	{
		char	b;
		char	g;
		char	r;
		char	a;
	};
}	t_color;

typedef struct s_app {
	t_array			map;
	t_coordinates	player;
	float			player_dir;
	bool			keys[6];
	void			*mlx;
	void			*win;
	size_t			win_h;
	size_t			win_w;
	float			mini_map_tile_h;
	float			mini_map_tile_w;
	size_t			mini_map_h;
	size_t			mini_map_w;
}	t_app;

bool	check_map(t_array map, t_coordinates player);
bool	init(int ac, char **av, t_app *papp);
t_image	image_new(void	*mlx, size_t width, size_t height);
void	image_delete(void	*mlx, t_image img);
void	image_put_px(t_image img, int x, int y, int color);
int		image_get_px_color(t_image img, int x, int y);
bool	draw_map(t_app *papp, t_image win_image);
void	draw_minimap(t_app *papp, t_image win_image);
int		destroy_and_exit(t_app *papp);
void	init_hooks(t_app *papp);

#endif