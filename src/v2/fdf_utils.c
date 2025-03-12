/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:33:33 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/12 13:30:27 by fvon-de          ###   ########.fr       */
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

void	free_grid(char **grid, int rows)
{
	int	i;

	if (grid)
	{
		i = 0;
		while (i < rows)
		{
			if (grid[i])
				free(grid[i]);
			i++;
		}
		free(grid);
	}
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_grid(map->grid_virt, map->rows);
	free_grid(map->grid, map->rows);
	free(map);
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
