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

void	cpy_pixel(t_mlx *mlx, int x, int y, int color)
{
	ft_memcpy(mlx->img_data + y * mlx->map.size_line + x
		* mlx->map.bits_per_pixel / 8, &color, mlx->map.bits_per_pixel / 8);
	if (mlx->map.lines > 100 || mlx->map.columns > 100)
		return ;
	ft_memcpy(mlx->img_data + y * mlx->map.size_line + (x + 1)
		* mlx->map.bits_per_pixel / 8, &color, mlx->map.bits_per_pixel / 8);
	ft_memcpy(mlx->img_data + (y + 1) * mlx->map.size_line + x
		* mlx->map.bits_per_pixel / 8, &color, mlx->map.bits_per_pixel / 8);
	ft_memcpy(mlx->img_data + (y + 1) * mlx->map.size_line + (x + 1)
		* mlx->map.bits_per_pixel / 8, &color, mlx->map.bits_per_pixel / 8);
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
