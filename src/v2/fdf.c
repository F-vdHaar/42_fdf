/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:01:14 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/04 12:59:32 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	init_fdf(t_fdf *fdf, char *filename);
static void	setup_hooks(t_fdf *fdf);
static int	run_fdf(t_fdf *fdf);

int main(int argc, char **argv)
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
		free(fdf);
		return (EXIT_FAILURE);
	}
	run_fdf(fdf);
	return (EXIT_SUCCESS);
}
static int	init_fdf(t_fdf *fdf, char *filename)
{

	fdf->map = parse_input(filename);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf->mlx)
	{
		free_map(fdf->map);
		log_error("Error: [init_fdf] mlx init");
		log_error(mlx_strerror(mlx_errno));
	}
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image)
	{
		free_map(fdf->map);
		mlx_close_window(fdf->mlx);
		log_error("Error: [init_fdf] image  init")
		log_error(mlx_strerror(mlx_errno));
	}
	return (EXIT_SUCCESS);
}

static void	setup_hooks(t_fdf *fdf)
{

}
static int	run_fdf(t_fdf *fdf)
{
    display_menu(fdf->mlx);
    draw_image(fdf);
    if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
	{
        log_error("Error: [run_fdf] Failed image to window");
        log_error(mlx_strerror(mlx_errno));
        cleanup(fdf);
        return (EXIT_FAILURE);
    }
    setup_hooks(fdf);
    mlx_loop(fdf->mlx);
    cleanup(fdf);
	return (EXIT_SUCCESS);
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
