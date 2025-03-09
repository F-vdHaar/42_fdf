/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:33:33 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/09 08:02:58 by fvon-de          ###   ########.fr       */
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
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
		{
			mlx_put_pixel(image, j, i, BACKGROUND);
			j++;
		}
		i++;
	}
}

void cleanup(t_fdf *fdf)
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
