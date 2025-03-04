/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:29:27 by fvon-der          #+#    #+#             */
/*   Updated: 2025/02/27 06:48:11 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // DEBUG: For printf

static void	handle_translate_key(t_renderer *renderer, int keycode);
static void	handle_scale_key(t_renderer *renderer, int keycode);
static void	handle_rotate_key(t_renderer *renderer, int keycode);
static void	handle_zoom_key(t_renderer *renderer, int keycode);

void	handle_mlx_keypress(mlx_key_data_t keydata, void *param)
{
	t_renderer	*renderer;

	renderer = (t_renderer *)param;
	renderer->need_redraw = 1;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(renderer->mlx);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D
		|| keydata.key == MLX_KEY_I || keydata.key == MLX_KEY_K)
		handle_translate_key(renderer, keydata.key);
	else if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
		handle_zoom_key(renderer, keydata.key);
	else if (keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_E
		|| keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT
		|| keydata.key == MLX_KEY_PAGE_UP || keydata.key == MLX_KEY_PAGE_DOWN)
		handle_rotate_key(renderer, keydata.key);
	else if (keydata.key == MLX_KEY_X || keydata.key == MLX_KEY_Y
		|| keydata.key == MLX_KEY_Z)
		handle_scale_key(renderer, keydata.key);
	else if (keydata.key == MLX_KEY_R)
		init_camera(renderer);
	else
		renderer->need_redraw = 0;
	draw_window(renderer);
}

static void	handle_rotate_key(t_renderer *renderer, int keycode)
{
	if (keycode == MLX_KEY_LEFT)
		handle_rotate(renderer, 0, 0.01, 0);
	else if (keycode == MLX_KEY_RIGHT)
		handle_rotate(renderer, 0, -0.01, 0);
	else if (keycode == MLX_KEY_UP)
		handle_rotate(renderer, 0.01, 0, 0);
	else if (keycode == MLX_KEY_DOWN)
		handle_rotate(renderer, -0.01, 0, 0);
	else if (keycode == MLX_KEY_PAGE_UP)
		handle_rotate(renderer, 0, 0, 0.01);
	else if (keycode == MLX_KEY_PAGE_DOWN)
		handle_rotate(renderer, 0, 0, -0.01);
}

static void	handle_scale_key(t_renderer *renderer, int keycode)
{
	if (keycode == MLX_KEY_X)
		handle_scale(renderer, 1.1, 1.0, 1.0);
	else if (keycode == MLX_KEY_Y)
		handle_scale(renderer, 1.0, 1.1, 1.0);
	else if (keycode == MLX_KEY_Z)
		handle_scale(renderer, 1.0, 1.0, 1.1);
	else if (keycode == MLX_KEY_R)
		handle_scale(renderer, 1.0, 1.0, 1.0);
}

static void	handle_zoom_key(t_renderer *renderer, int keycode)
{
	if (keycode == MLX_KEY_EQUAL)
		handle_zoom(renderer, IN_ZOOM);
	else if (keycode == MLX_KEY_MINUS)
		handle_zoom(renderer, OUT_ZOOM);
}

static void	handle_translate_key(t_renderer *renderer, int keycode)
{
	if (keycode == MLX_KEY_W)
		handle_translate(renderer, 0, -10, 0);
	else if (keycode == MLX_KEY_S)
		handle_translate(renderer, 0, 10, 0);
	else if (keycode == MLX_KEY_A)
		handle_translate(renderer, -10, 0, 0);
	else if (keycode == MLX_KEY_D)
		handle_translate(renderer, 10, 0, 0);
	else if (keycode == MLX_KEY_I)
		handle_translate(renderer, 0, 0, 10);
	else if (keycode == MLX_KEY_K)
		handle_translate(renderer, 0, 0, -10);
}
