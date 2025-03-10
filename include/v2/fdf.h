/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:05:29 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/10 10:39:24 by fvon-der         ###   ########.fr       */
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
# include "MLX42.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define WIDTH				800
# define HEIGHT				600
# define ROT_ANGLE			5
# define ZOOM_STEP			1.1
# define SCALE_STEP			1.1

typedef struct s_point_virt
{
	double	x;
	double	y;
	double	z;
	int		col;
}				t_point_virt;

typedef struct s_point
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
	double			x_offset;
	double			y_offset;
	double			interval;
	double			alpha;
	double			beta;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	double			zoom;
	double			scale_x;
	double			scale_y;
	double			scale_z;
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
// hooks add
void		resize_hook(int32_t width, int32_t height, void *param);
/* fdf_utils.c*/
void		make_upper(unsigned int i, char *c);
void		draw_reset(mlx_image_t *image);
int			valid_filename(const char *filename);
/* fdf_color.c */
int			get_color(t_point current, t_point a, t_point b);
void		set_zcolor(t_map *map);

#endif
