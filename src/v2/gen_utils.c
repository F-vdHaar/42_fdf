/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:22:39 by fvon-de           #+#    #+#             */
/*   Updated: 2025/03/08 18:24:44 by fvon-de          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void log_error(const char *message)
{
    // Print the error message to the terminal
    ft_printf("Error: %s\n", message);

    // Open the log file (append mode)
    int fd = open("error_log.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1)
    {
        ft_printf("Error: Failed to open log file\n");
        return;
    }

    // Write the error message to the log file
    ft_printf("Error: %s\n", message);  // Using ft_printf to write to file
    close(fd);
}

