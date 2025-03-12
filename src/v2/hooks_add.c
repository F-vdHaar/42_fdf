/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 07:29:01 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/12 14:05:36 by fvon-de          ###   ########.fr       */
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
