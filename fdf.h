/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:10 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 02:36:14 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// MESSAGE
# define PATH_INVALID "FDF MAP PATH INVALID\n"
# define MAP_INVALID "FDF MAP INVALID\n"

// KEY
# define ESC 65307
# define R 114
# define W 119
# define A 97
# define S 115
# define D 100
# define U 117
# define J 106
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define SCROLL_UP 4
# define SCROLL_DOWN 5

// STRUCT

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct map
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		**numbers;
	int		lines;
	int		columns;
	int		zoom;
	int		toogle_map;
	int		upper;
	int		move_x;
	int		move_y;
}			t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*img_data;
	int		width;
	int		height;
	t_map	map;
}			t_mlx;

// FDF
void		clear_image(t_mlx *mlx);
int			mlx_start(t_mlx *mlx, int reset, int draw);

// hook mouse
int			init_hook(t_mlx *mlx);
int			key_hook(int key, t_mlx *mlx);
int			key_hook2(int key, t_mlx *mlx);
int			mouse_hook(int button, int x, int y, t_mlx *mlx);
int			close_window(t_mlx *mlx);

// read
int			read_file(char *filepath, t_mlx *mlx);
int			control_line(char *line, int *numbers);
int			count_lines(char *filepath, t_mlx *mlx);
int			count_numbers(char *line);
void		free_map(t_map *map);

// draw
int			get_color(t_point a, t_point b, double ratio);
t_point		*convert_point(int x, int y, t_mlx *mlx);
void		choice_color(int x, int y, t_mlx *mlx, t_point *point);

// draw 2
void		draw_map(t_mlx *mlx);
void		cpy_pixel(t_mlx *mlx, int x, int y, int color);
void		draw_line(t_mlx *mlx, t_point a, t_point b);

// tools
void		start(t_mlx *mlx, char *filepath, int ac, char **av);
void		stop(t_mlx mlx);
int			draw_menu(t_mlx *mlx);
int			iso_x(int x, int y);
int			iso_y(int x, int y, int z);

#endif