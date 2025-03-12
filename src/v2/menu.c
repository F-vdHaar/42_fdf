/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:35:15 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/12 12:53:15 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Display controls menu
void	display_controls_menu(mlx_t *mlx, int x, int y)
{
	mlx_put_string(mlx, "Menu", x, y);
	mlx_put_string(mlx, "Translate \t\t\t\tArrow Keys", x, y += 20);
	mlx_put_string(mlx, "Rotate X \t\t\tR / F", x, y += 20);
	mlx_put_string(mlx, "Rotate Y \t\t\tT / G", x, y += 20);
	mlx_put_string(mlx, "Rotate Z \t\t\tH / J", x, y += 20);
	mlx_put_string(mlx, "Stretch X \t\t\tQ / E", x, y += 20);
	mlx_put_string(mlx, "Stretch Y \t\t\tA / D", x, y += 20);
	mlx_put_string(mlx, "Stretch Z \t\t\tZ / X", x, y += 20);
	mlx_put_string(mlx, "Zoom  \t\t\t NUMPAD 1 / 2", x, y += 20);
	mlx_put_string(mlx, "View  \t\t\t 1 / 2 / 3", x, y += 20);
	mlx_put_string(mlx, "Reset\t\t\tSpace", x, y += 30);
	mlx_put_string(mlx, "Values \t\t\tC", x, y += 30);
	mlx_put_string(mlx, "Exit\t\t\tEscape", x, y += 20);
}

void	display_menu(mlx_t *mlx)
{
	int	x;
	int	y;

	y = 50;
	x = 20;
	display_controls_menu(mlx, x, y);
}
