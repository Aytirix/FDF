/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:44 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 02:35:28 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	start(t_mlx *mlx, char *filepath, int ac, char **av)
{
	if (ac != 2)
		ft_putstr_fd(PATH_INVALID, 1);
	else if (!count_lines(filepath, mlx))
		ft_putstr_fd(MAP_INVALID, 1);
	else
	{
		if (!read_file(av[1], mlx))
		{
			free_map(&mlx->map);
			exit(1);
		}
		mlx->mlx = mlx_init();
		mlx_get_screen_size(mlx->mlx, &mlx->width, &mlx->height);
		mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "FDF");
		mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
		mlx->img_data = mlx_get_data_addr(mlx->img, &mlx->map.bits_per_pixel,
				&mlx->map.size_line, &mlx->map.endian);
		init_hook(mlx);
		draw_menu(mlx);
		return ;
	}
	exit(1);
}

void	stop(t_mlx mlx)
{
	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	free_map(&mlx.map);
	exit(0);
}

int	draw_menu(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, 20, 20, 0xFF0000, "Menu  :");
	mlx_string_put(mlx->mlx, mlx->win, 20, 40, 0xFF0000, "ESC   : Quit");
	mlx_string_put(mlx->mlx, mlx->win, 20, 60, 0xFF0000, "ZOOM  : Mouse wheel");
	mlx_string_put(mlx->mlx, mlx->win, 20, 80, 0xFF0000,
		"U / J : UP / DOWN Number");
	mlx_string_put(mlx->mlx, mlx->win, 20, 100, 0xFF0000,
		"WASD  : MOVE MAP");
	mlx_string_put(mlx->mlx, mlx->win, 20, 120, 0xFF0000,
		"RESET : R");
	return (0);
}

int	iso_x(int x, int y)
{
	return (x - y);
}

int	iso_y(int x, int y, int z)
{
	return ((x + y) / 2 - z);
}
