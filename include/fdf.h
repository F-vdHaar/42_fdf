/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:10:04 by fvon-der          #+#    #+#             */
/*   Updated: 2025/02/18 21:45:20 by fvon-de          ###   ########.fr       */
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
# include <X11/keysym.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h" 
# include "ft_printf.h" 

# define MIN_ZOOM 1
# define MAX_ZOOM 100
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define MOUSE_LEFT_BUTTON 1
# define ROTATE_MODE 0
# define TRANSLATE_MODE 1
# define SCALE_MODE 2

// Keycodes
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_Z_TRANSLATE 6
# define KEY_ZOOM_IN 24
# define KEY_ZOOM_OUT 27
# define KEY_ROTATE_LEFT 0
# define KEY_ROTATE_RIGHT 2
# define KEY_ROTATE_X_UP 13
# define KEY_ROTATE_X_DOWN 1
# define KEY_ROTATE_Z_LEFT 12
# define KEY_ROTATE_Z_RIGHT 14
# define KEY_STRETCH_X 7
# define KEY_STRETCH_Y 16
# define KEY_STRETCH_Z 8

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int		color;
}	t_point;

typedef struct s_map
{
	int		**grid;
	int		width;
	int		height;
	int		z_min;
	int		z_max;
	t_list	*file_content;
}	t_map;

typedef struct s_camera
{
	int		zoom;
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

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_mouse
{
	int		is_pressed;
	int		prev_x;
	int		prev_y;
	int		x;
	int		y;
	int		button;
}	t_mouse;

typedef struct s_renderer
{
	t_mlx		mlx;
	t_map		*map;
	t_camera	*camera;
	t_mouse		*mouse;
	int			win_width;
	int			win_height;
	int			is_focused;
	float		*z_buffer;
	int			keymode;
}	t_renderer;

// Function prototypes
// FDF functions
int    initialize(t_renderer *renderer, char *filename);
int     main(int argc, char **argv);
int    cleanup(t_renderer *renderer);

// Camera functions
int     init_camera(t_renderer *renderer); // Added return type
int    reset_camera(t_renderer *renderer);
t_point	project_point(t_renderer *renderer, int x, int y, int z);

// Event handling
int     handle_close(t_renderer *renderer);
int     handle_keypress(int keycode, t_renderer *renderer);
int    setup_event_hooks(t_renderer *renderer);

// Line
int    draw_map_line(t_renderer *renderer, t_map *map); // If needed
int    draw_line(t_renderer *renderer, t_point *start, t_point *end);
int    init_line_params(t_point start, t_point end, t_point *delta, t_point *sign);

// Draw
int    bresenham_draw(t_renderer *renderer, t_point *start, t_point *end);
int    render_map(t_renderer *renderer);

// Color utils
int     get_color(t_map *map, int x, int y);
int     i_color(int color1, int color2, double t);

// Map functions
int		init_map(t_renderer *renderer, const char *filename);
int    find_z_bounds(t_map *map);

// Map utilities
int     **allocate_map(int height, int width);
int     count_words(const char *str, char delimiter);
int    free_map(t_map *map);
int    free_string_array(char **arr);
int    fix_negative_numbers(char **nums);

// Mouse handling
int     handle_mouse_move(int x, int y, t_renderer *renderer);
int     handle_mouse_press(int button, int x, int y, t_renderer *renderer);
int     handle_mouse_release(t_renderer *renderer);
int    handle_mouse_zoom(t_renderer *renderer, int button);
int	    init_mouse(t_renderer *renderer);

// Renderer functions
int     init_renderer(t_renderer *renderer); // Added return type
int    put_pixel(t_renderer *renderer, int x, int y, int color);
int		init_image(t_renderer *renderer); // Added prototype

// Transformations
int    handle_rotate(t_renderer *renderer, double x_angle, double y_angle, double z_angle);
int    handle_scale(t_renderer *renderer, double x_scale, double y_scale, double z_scale);
int    handle_translate(t_renderer *renderer, double dx, double dy);
int    handle_zoom(t_renderer *renderer, double factor);
int    rotate_point(t_point *point, t_camera *camera);

// Debug Utility functions
int    log_error(const char *message);
int    print_map(int **map);
int    debug_render_grid(t_renderer *renderer);

#endif
