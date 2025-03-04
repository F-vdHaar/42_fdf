/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:10:04 by fvon-der          #+#    #+#             */
/*   Updated: 2025/02/27 08:17:03 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include "MLX42.h"
# include "libft.h"
# include "get_next_line.h" 
# include "ft_printf.h" 

// Event handling and queue
# define MAX_EVENTS 100

// Zoom Constants
# define MIN_ZOOM 1.0  // Minimum zoom factor
# define MAX_ZOOM 100.0 // Maximum zoom factor
# define OUT_ZOOM 0.9
# define IN_ZOOM 1.1

// Scale Constants
# define MIN_SCALE 0.1 // Minimum scale factor
# define MAX_SCALE 10.0 // Maximum scale factor
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define MOUSE_LEFT_BUTTON 1
# define ROTATE_MODE 0
# define TRANSLATE_MODE 1
# define SCALE_MODE 2

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}	t_point;

typedef struct s_map
{
	int		**grid;
	int		**color;
	int		width;
	int		height;
	int		z_min;
	int		z_max;
	t_list	*file_content;
}	t_map;

typedef struct s_camera
{
	float	zoom;
	float	x_angle;
	float	y_angle;
	float	z_angle;
	float	z_height;
	int		x_offset;
	int		y_offset;
	float	x_scale;
	float	y_scale;
	float	z_scale;
	int		iso;
}	t_camera;

typedef struct s_renderer
{
	mlx_t			*mlx;
	t_map			*map;
	t_camera		*camera;
	int				win_width;
	int				win_height;
	int				is_focused;
	int				keymode;
	mlx_image_t		*image;
	int				need_redraw;
}	t_renderer;

// Function prototypes

// FDF functions
int		initialize(t_renderer *renderer, char *filename);
int		main(int argc, char **argv);

// FDF Utilities
int		cleanup(t_renderer *renderer);
int		draw_window(t_renderer *renderer);

// Camera functions
int		init_camera(t_renderer *renderer);
int		reset_camera(t_renderer *renderer);
t_point	project_point(t_renderer *renderer, int x, int y, int z);

// Event handling (MLX42 style)
int		setup_event_hooks(t_renderer *renderer);

// MLX Events
void	handle_mlx_keypress(mlx_key_data_t keydata, void *param);
void	handle_mlx_mouse_press(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);
void	handle_mlx_mouse_release(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);
void	handle_mlx_mouse_move(double xpos, double ypos, void *param);
void	handle_mlx_scroll(double xdelta, double ydelta, void *param);
int		handle_mlx_close(void *param);
int		handle_mlx_resize(int32_t width, int32_t height, void *param);

// Line drawing
int		draw_map_line(t_renderer *renderer, t_map *map);
int		draw_line(t_renderer *renderer, t_point *start, t_point *end);
int		init_line_params(t_point start, t_point end,
			t_point *delta, t_point *sign);

// Drawing functions
int		bresenham_draw(t_renderer *renderer, t_point *start, t_point *end);
int		render_map(t_renderer *renderer);

// Projection
t_point	project_point(t_renderer *renderer, int x, int y, int z);

// Rotation
t_point	rotate_point(t_renderer *renderer, t_point point);

// Color utilities
int		get_color(t_map *map, int x, int y);
int		i_color(int color1, int color2, double t);

// Map functions
int		init_map(t_renderer *renderer, const char *filename);
int		find_z_bounds(t_map *map);

// Map utilities
int		**allocate_map(int height, int width);
int		count_words(const char *str, char delimiter);
int		free_map(t_map *map);
int		free_string_array(char **arr);
int		fix_negative_numbers(char **nums);

// Mouse handling (using MLX42)
int		handle_mouse_zoom(t_renderer *renderer,
			mouse_key_t button); // Handle mouse zoom
int		init_mouse(t_renderer *renderer); // Initialize mouse handling

// Renderer functions
int		init_renderer(t_renderer *renderer);
int		put_pixel(t_renderer *renderer, int x, int y, int color);
int		init_image(t_renderer *renderer);

// Transformations
int		handle_rotate(t_renderer *renderer, double x_angle,
			double y_angle, double z_angle);
int		handle_scale(t_renderer *renderer, double x_scale,
			double y_scale, double z_scale);
int		handle_translate(t_renderer *renderer, double dx, double dy, double dz);
int		handle_zoom(t_renderer *renderer, double factor);

// Debug Utility functions
int		log_error(const char *message);
int		print_map(int **map);
int		debug_render_grid(t_renderer *renderer);
int		debug_print_nums_char(char **nums);
int		debug_print_map(t_renderer *renderer);

#endif