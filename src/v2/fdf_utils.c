/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:00:37 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/04 12:53:18 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	print_map(int **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != -1)
		{
			ft_printf("%d ", map[i][j]);
			j++;
		}
		if (write(1, "\n", sizeof(char)) == -1)
			log_error("Error: [print_map] Error writing to standard output");
		i++;
	}
	return (EXIT_SUCCESS);
}

//    ft_printf(file, "%s\n", message);
int	log_error(const char *message)
{
	FILE	*file;

	file = fopen("error.log", "a");
	if (file == NULL)
	{
		ft_printf("Could not open error.log for writing\n");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", message);
	fclose(file);
	return (EXIT_SUCCESS);
}

