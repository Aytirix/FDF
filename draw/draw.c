/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:49 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 04:05:20 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	get_color(t_point a, t_point b, double ratio)
{
	int	color;
	int	r;
	int	g;
	int	bl;

	r = (a.color >> 16) + ((b.color >> 16) - (a.color >> 16)) * ratio;
	g = (a.color >> 8 & 0xFF) + ((b.color >> 8 & 0xFF) - (a.color >> 8 & 0xFF))
		* ratio;
	bl = (a.color & 0xFF) + ((b.color & 0xFF) - (a.color & 0xFF)) * ratio;
	color = r << 16 | g << 8 | bl;
	return (color);
}

t_point	*convert_point(int x, int y, t_mlx *mlx)
{
	t_point	*point;
	int		temp;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		stop(*mlx);
	point->z = mlx->map.numbers[y][x];
	if (point->z != 0)
		point->z = point->z / 5 + mlx->map.upper;
	point->z *= mlx->map.zoom;
	point->x = (x - mlx->map.columns / 2) * mlx->map.zoom;
	point->y = (y - mlx->map.lines / 2) * mlx->map.zoom;
	temp = iso_x(point->x, point->y);
	point->y = iso_y(point->x, point->y, point->z) + mlx->map.move_y
		+ mlx->height / 2;
	point->x = temp + mlx->map.move_x + mlx->width / 2;
	choice_color(x, y, mlx, point);
	return (point);
}

void	choice_color(int x, int y, t_mlx *mlx, t_point *point)
{
	if (mlx->map.numbers[y][x] == 0)
		point->color = 0x6a329f;
	else if (mlx->map.numbers[y][x] <= 10)
		point->color = 0xf1c232;
	else if (mlx->map.numbers[y][x] <= 20)
		point->color = 0x00FF00;
	else if (mlx->map.numbers[y][x] <= 30)
		point->color = 0xff8200;
	else
		point->color = 0x148feb;
}
