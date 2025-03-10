/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 07:29:01 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/10 11:11:16 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setup_hooks(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, &key_hook_std, fdf);
	mlx_loop_hook(fdf->mlx, &rotate_hook, fdf);
	mlx_loop_hook(fdf->mlx, &view_hook, fdf);
	mlx_resize_hook(fdf->mlx, &resize_hook, fdf);
	mlx_loop_hook(fdf->mlx, &draw_image, fdf);
}



static void	reset_map(t_map *map)
{
	map->beta = 0.463;
	map->alpha = map->beta / 2;
	map->rot_x = 0;
	map->rot_y = 0;
	map->rot_z = 0;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->zoom = 1;
	map->scale_x = 1;
	map->scale_y = 1;
	map->scale_z = 1;
}

void	key_hook_std(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_SPACE))
		reset_map(fdf->map);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->map->x_offset -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->map->x_offset += 5; 
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->map->y_offset += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->map->y_offset -= 5;

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
		fdf->map->alpha =  0.232;
		fdf->map->beta = 0.464;
	}
}

void	rotate_hook(void *param)
{
	t_fdf	*fdf;
	double	sign;

	fdf = (t_fdf *) param;
	sign = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_COMMA))
		sign = -1;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_PERIOD))
		sign = 1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->map->alpha += sign * 0.03;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->map->beta += sign * 0.03;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->map->zscale += sign * 0.03;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X))
		fdf->map->xrotate += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y))
		fdf->map->yrotate += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z))
		fdf->map->zrotate += sign * 0.02;
}
