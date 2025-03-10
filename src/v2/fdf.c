/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 07:19:23 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/10 10:43:27 by fvon-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	run_fdf(t_fdf *fdf);
static int	init_fdf(t_fdf *fdf, char *filename);

static void	malloc_grid(t_map *map)
{
	
	int	i;

	map->grid_virt = malloc(sizeof(t_point_virt *) * map->rows);
	map->grid = malloc(sizeof(t_point *) * map->rows);
	if (!(map->grid) || !(map->grid_virt))
	{
		free_map(map);
		log_error("[malloc_grid] Allocation failed");
	}
	i = -1;
	while (++i < map->rows)
	{
		map->grid_virt[i] = malloc(sizeof(t_point_virt) * map->cols);
		map->grid[i] = malloc(sizeof(t_point) * map->cols);
		if (!(map->grid[i]) || !(map->grid_virt[i]))
		{
			if (i + 1 < map->rows)
			{
				map->grid_virt[i + 1] = NULL;
				map->grid[i + 1] = NULL;
			}
			free_map(map);
			log_error("[malloc_grid] Row Allocation failed");		}
	}
}

static t_map	*parse_input(char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
		log_error("[parse_inout] Can't open file");
	map = malloc(sizeof(t_map));
	if (!map)
	{
		close(fd);
		log_error("[parse_inout] Allocate Map failed");
	}
	init_map(map);
	get_dimensions(fd, map);
	close(fd);
	malloc_grid(map);
	map->interval = ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 2;
	map->interval = ft_max(2, map->interval);
	fd = open(filename, O_RDONLY, 0777);
	parse_map(fd, map);
	close(fd);
	return (map);
}


int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	
	if (argc != 2) {
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	fdf = malloc(sizeof(t_fdf));
	if (!fdf) {
		log_error("Error: [main] Failed to allocate memory for renderer");
		return (EXIT_FAILURE);
	}
	memset(fdf, 0, sizeof(t_fdf));
	if (init_fdf(fdf, argv[1]) != EXIT_SUCCESS) {
		log_error("Error: [main] Failed to init fdf");
		cleanup(fdf);
		return (EXIT_FAILURE);
	}
	run_fdf(fdf);
	cleanup(fdf);
	return (EXIT_SUCCESS);
}
static int	init_fdf(t_fdf *fdf, char *filename) {
	fdf->map = parse_input(filename);
	if (!fdf->map) {
		log_error("Error: [init_fdf] parse_input failed");
		return (EXIT_FAILURE);
	}
	ft_printf("DEBUG: [init_fdf] 1 FULL SUCCESS\n");
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf->mlx) {
		cleanup(fdf);
		log_error("Error: [init_fdf] mlx init");
		log_error(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image) {
		cleanup(fdf);
		mlx_close_window(fdf->mlx);
		log_error("Error: [init_fdf] image  init");
		log_error(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	ft_printf("DEBUG: [init_fdf] FULL SUCCESS\n");
	return (EXIT_SUCCESS);
}


static int	run_fdf(t_fdf *fdf)
{
	display_menu(fdf->mlx);
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
	{
		log_error("Error: [run_fdf] Failed image to window");
		log_error(mlx_strerror(mlx_errno));
		cleanup(fdf);
		return (EXIT_FAILURE);
	}
	draw_image(fdf);
	setup_hooks(fdf);
	mlx_loop(fdf->mlx);
	return (EXIT_SUCCESS);
}


