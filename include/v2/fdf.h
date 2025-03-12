/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:05:29 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/12 14:00:16 by fvon-de          ###   ########.fr       */
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

# define WIDTH				1200
# define HEIGHT				800
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

// **color.c**
int i_color(int color1, int color2, double t);
int get_color(t_point current, t_point a, t_point b);

// **fdf_utils.c**
void project(t_map *map, int i, int j);
void make_upper(unsigned int i, char *c);
void ft_free_tab(void **tab, size_t len);
void cleanup(t_fdf *fdf);
int ft_max(int a, int b);
int ft_min(int a, int b);
void log_error(const char *message);

// **gen_utils.c**
void reset_map(t_map *map);
void free_grid(char **grid, int rows);
void free_map(t_map *map);

// **map.c**
void init_map(t_map *map);

// **rotate.c**
void rotate_x(double *y, double *z, double alpha);
void rotate_y(double *x, double *z, double beta);
void rotate_z(double *x, double *y, double gamma);

// **draw.c**
void draw_image(void *param);
void draw_reset(mlx_image_t *image);

// **hooks_add.c**
void move_hook(t_fdf *fdf);
void rotate_hook(t_fdf *fdf);
void stretch_hook(t_fdf *fdf);
void zoom_hook(t_fdf *fdf);

// **menu.c**
void display_controls_menu(mlx_t *mlx, int x, int y);
void display_menu(mlx_t *mlx);

// **fdf.c**
int main(int argc, char **argv);
void setup_hooks(t_fdf *fdf);
void key_hook_std(void *param);
void view_hook(void *param);

// **hooks.c**
void resize_hook(int32_t width, int32_t height, void *param);

// **parse.c**
void parse_map(int fd, t_map *map);
void get_dimensions(int fd, t_map *map);

#endif
