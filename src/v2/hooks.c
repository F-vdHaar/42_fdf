/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:08:01 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/12 13:34:58 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Move map position
void	move_hook(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->map->x_offset -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->map->x_offset += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->map->y_offset += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->map->y_offset -= 5;
}

// Rotate map
void	rotate_hook(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
		fdf->map->rot_x += 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F))
		fdf->map->rot_x -= 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_T))
		fdf->map->rot_y += 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_G))
		fdf->map->rot_y -= 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_H))
		fdf->map->rot_z += 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_J))
		fdf->map->rot_z -= 0.02;
}

// Stretch map
void	stretch_hook(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->map->scale_x *= 1.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->map->scale_x *= 0.98;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->map->scale_y *= 1.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->map->scale_y *= 0.98;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z))
		fdf->map->scale_z *= 1.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X))
		fdf->map->scale_z *= 0.98;
}

// Zoom map
void	zoom_hook(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_1))
		fdf->map->zoom *= 1.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_2))
		fdf->map->zoom *= 0.9;
}

void	view_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
	{
		fdf->map->alpha = 1.047;
		fdf->map->beta = fdf->map->alpha;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
	{
		fdf->map->alpha = 0.785;
		fdf->map->beta = fdf->map->alpha;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3))
	{
		fdf->map->alpha = 0.232;
		fdf->map->beta = 0.464;
	}
}

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

// Display current values in terminal
void	display_current_values_terminal(t_fdf *fdf)
{
	ft_printf("\nCurrent Values:\n");
	ft_printf("----------------------------\n");
	ft_printf("Rotation X:   %.1f\n", fdf->map->rot_x);
	ft_printf("Rotation Y:   %.1f\n", fdf->map->rot_y);
	ft_printf("Rotation Z:   %.1f\n", fdf->map->rot_z);
	ft_printf("----------------------------\n");
	ft_printf("Scale X:      %.1f\n", fdf->map->scale_x);
	ft_printf("Scale Y:      %.1f\n", fdf->map->scale_y);
	ft_printf("Scale Z:      %.1f\n", fdf->map->scale_z);
	ft_printf("----------------------------\n");
	ft_printf("Zoom:         %.1f\n", fdf->map->zoom);
	ft_printf("X Offset:     %.1f\n", fdf->map->x_offset);
	ft_printf("Y Offset:     %.1f\n", fdf->map->y_offset);
	ft_printf("----------------------------\n");
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
