/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:08:01 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/12 14:05:49 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Reset map to default values
void	reset_map(t_map *map)
{
	map->beta = 0.463;
	map->alpha = map->beta / 2;
	map->rot_x = 0;
	map->rot_y = 0;
	map->rot_z = 0;
	map->x_offset = 2 * (WIDTH / 3);
	map->y_offset = HEIGHT / 2;
	map->zoom = 1;
	map->scale_x = 1;
	map->scale_y = 1;
	map->scale_z = 1;
	ft_printf("[DEBUG] Map reset.\n");
}

// Key event handler for standard transformations and actions
void	key_hook_std(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_SPACE))
		reset_map(fdf->map);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	move_hook(fdf);
	rotate_hook(fdf);
	stretch_hook(fdf);
	zoom_hook(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_C))
		display_current_values_terminal(fdf);
}

// Set up hooks for handling key presses
void	setup_hooks(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, &key_hook_std, fdf);
	mlx_resize_hook(fdf->mlx, &resize_hook, fdf);
	mlx_loop_hook(fdf->mlx, &draw_image, fdf);
	mlx_loop_hook(fdf->mlx, &view_hook, fdf);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	if (fdf->image)
	{
		mlx_delete_image(fdf->mlx, fdf->image);
	}
	fdf->image = mlx_new_image(fdf->mlx, width, height);
	if (!fdf->image)
	{
		log_error("[resize_hook] Failed to create new image");
		return ;
	}
	draw_reset(fdf->image);
	draw_image(fdf);
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
	{
		log_error("[resize_hook] Failed to put image to window");
	}
}
