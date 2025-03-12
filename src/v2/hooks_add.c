/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 07:29:01 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/12 13:26:01 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
