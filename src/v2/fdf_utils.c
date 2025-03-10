/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:33:33 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/10 07:43:53 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_upper(unsigned int i, char *c)
{
	i++;
	*c = ft_toupper(*c);
}

void	ft_free_tab(void **tab, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_map *map)
{
	int i;
	if (map == NULL)
		return ;
	if (map->grid_virt != NULL)
	{
		i = 0;
		while (i < map->rows)
		{
			if (map->grid_virt[i] != NULL)
				free(map->grid_virt[i]);
			i++;
		}
		free(map->grid_virt);
	}
	if (map->grid != NULL)
	{
		i = 0;
		while (i < map->rows)
		{
			if (map->grid[i] != NULL)
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

void	draw_reset(mlx_image_t *image)
{
	size_t	image_size;

	if (image == NULL)
		return ;
	image_size = image->width * image->height * 4;
	memset(image->pixels, 0, image_size);
}

void	cleanup(t_fdf *fdf)
{
	if (fdf)
	{
		if (fdf->map)
		{
			free_map(fdf->map);
		}
		if (fdf->mlx)
		{
			mlx_terminate(fdf->mlx);
		}
		free(fdf);
	}
}
