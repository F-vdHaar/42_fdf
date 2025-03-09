/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:05:29 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/09 07:36:04 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include "../../lib/MLX42/include/MLX42/MLX42.h"
# include "../../lib/lib42/libft/include/libft.h"
# include "../../lib/lib42/gnl/include/get_next_line.h"
# include "../../lib/lib42/ft_printf/include/ft_printf.h"

# define WIDTH				1920
# define HEIGHT				1080
# define TEXT_COLOR			0xEAEAEAFF
# define BACKGROUND			0x22222200
# define MENU_BACKGROUND	0x1E1E1EFF
# define COLOR_TEN			0x9e0142ff
# define COLOR_NINE			0xd53e4fff
# define COLOR_EIGHT		0xf46d43ff
# define COLOR_SEVEN		0xfdae61ff
# define COLOR_SIX			0xfee08bff
# define COLOR_FIVE			0xe6f598ff
# define COLOR_FOUR			0xabdda4ff
# define COLOR_THREE		0x66c2a5ff
# define COLOR_TWO			0x3288bdff
# define COLOR_ONE			0x5e4fa2ff
# define FORMAT				"Format:\n\t./fdf maps/filename.fdf"
# define MALLOC				"Malloc failed"
# define INVALID_MAP		"Map is invalid"
# define FILE_ERROR			"Unable to open file"

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
	int		zcolor;
}				t_point_virt;

typedef struct s_point2d
{
	int		x;
	int		y;
	int		z;
	int		col;
}			t_point;

typedef struct s_map
{
	int				rows;
	int				cols;
	int				high;
	int				low;
	bool			use_zcolor;
	double			x_offset;
	double			y_offset;
	double			interval;
	double			alpha;
	double			beta;
	double			xrotate;
	double			yrotate;
	double			zrotate;
	double			zoom;
	double			zscale;
	t_point_virt	**grid_virt;
	t_point		**grid;
}					t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*image;
}				t_fdf;

/* fdf_main.c */
void		init_map(t_map *map);
//
void cleanup(t_fdf *fdf);

// general utils
void log_error(const char *message);
int ft_max(int a, int b);
int ft_min(int a, int b);
// map 
t_map	*get_map(t_map	*map ,char *filename);

/* fdf_parse.c */
void		parse_map(int fd, t_map *map);
void		get_dimensions(int fd, t_map *map);
/* fdf_error.c */
void		ft_free_tab(void **ptr, size_t len);
void		free_map(t_map *map);
void		handle_error(const char *message);
void		error_map(int fd, t_map *map, char *message);
/* fdf_draw.c */
void		project(t_map *map, int i, int j);
void		draw_image(void *param);
void		display_menu(mlx_t *mlx);
/* fdf_rotate.c */
void		rotate_x(double *y, double *z, double alpha);
void		rotate_y(double *x, double *z, double beta);
void		rotate_z(double *x, double *y, double gamma);
/* fdf_hooks.c */
void		setup_hooks(t_fdf *fdf);
void		key_hook_std(void *param);
void		fdf_scrollhook(double xdelta, double ydelta, void *param);
void		rotate_hook(void *param);
void		view_hook(void *param);
/* fdf_utils.c*/
void		make_upper(unsigned int i, char *c);
void		draw_reset(mlx_image_t *image);
int			valid_filename(const char *filename);
/* fdf_color.c */
int			get_color(t_point current, t_point a, t_point b);
void		set_zcolor(t_map *map);

#endif
