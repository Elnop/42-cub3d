/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:01:40 by lperroti          #+#    #+#             */
/*   Updated: 2023/12/20 12:34:20 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define XK_MISCELLANY
# define XK_LATIN1
# include "../libs/minilibx-linux/mlx.h"
# include <X11/keysymdef.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../libs/liblp_c/liblp.h"

# define WIN_H 700
# define WIN_W 1200
# define MAP_SIZE 0.2
# define MOVE_STEP 0.10
# define ROTATE_STEP 0.01
# define FOV 0.36 // FRACTION OF 180
# define TEXTURE_H 100
# define TEXTURE_W 100

# define HELPER "./cub3d <map file>\n"

typedef struct s_xy {
	double	x;
	double	y;
}	t_xy;

typedef struct s_wall {
	t_xy		wall;
	t_xy		impact;
	t_xy		cam_point;
	double		len;
	double		angle;
	int			is_vertical;
}	t_wall;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_texture {
	t_image	img;
	int		h;
	int		w;
}	t_texture;

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
	char			**map;
	t_xy			p;
	double			p_dir;
	bool			keys[6];
	void			*mlx;
	void			*win;
	size_t			win_h;
	size_t			win_w;
	double			tile_h;
	double			tile_w;
	size_t			mini_map_h;
	size_t			mini_map_w;
	t_color			floor;
	t_color			ceil;
	t_texture		texno;
	t_texture		texso;
	t_texture		texea;
	t_texture		texwe;
	size_t			ray_i;
	t_xy			plane;
	t_wall			*rays;
}	t_app;

// INIT
bool			init(int ac, char **av, t_app *papp);
bool			init_map(t_app *papp, char *filename);
bool			set_player(t_app *papp, double x, double y, char cardinal);
bool			check_map(t_array map, t_xy p);
// UTILS
int				destroy_and_exit(t_app *papp);
t_image			image_new(void	*mlx, size_t width, size_t height);
void			image_delete(void	*mlx, t_image img);
void			image_put_px(t_image img, int x, int y, int color);
int				tex_get_px_color(t_texture tex, int x, int y);
void			draw_line(t_image win_image, t_xy s, t_xy e, int c);
void			draw_rect(t_image img, t_xy s, t_xy lengths, int color);
t_xy			*get_wall_limits(t_xy player, t_xy w, int side);
// RENDER
void			draw_minimap(t_app *papp, t_image win_image);
t_xy			rad_to_vect(double angle);
void			draw_walls(t_app *papp, t_image img);
t_texture		load_tex(void *mlx, char *filename);
bool			init_textures(t_app *papp, int map_fd);
t_array			get_walls(t_app *papp);
t_xy			lines_intersection(t_xy p1, t_xy p2, t_xy p3, t_xy p4);
// HOOKS
void			init_hooks(t_app *papp);
void			go_front(t_app *papp);
void			go_back(t_app *papp);
void			go_left(t_app *papp);
void			go_right(t_app *papp);
bool			init_player(t_app *papp);
#endif