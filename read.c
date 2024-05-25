/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:49 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/14 21:09:09 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_file(char *filepath, t_mlx *mlx)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd(PATH_INVALID, 1), 0);
	mlx->map.numbers = malloc(sizeof(int *) * (mlx->map.lines + 1));
	if (!mlx->map.numbers)
		return (0);
	mlx->map.numbers[mlx->map.lines] = NULL;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		mlx->map.numbers[i] = malloc(sizeof(int) * count_numbers(line));
		if (!mlx->map.numbers[i])
			return (0);
		if (!control_line(line, mlx->map.numbers[i]))
			return (ft_putstr_fd(MAP_INVALID, 1), 0);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (close(fd) + 1);
}

int	control_line(char *line, int *numbers)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i + 1])
			numbers[j] = ft_atoi(&line[i]);
		j++;
		while (line[i] && line[i] != ' ')
			i++;
	}
	return (1);
}

int	count_lines(char *filepath, t_mlx *mlx)
{
	char	*line;
	int		fd;

	mlx->map.lines = 0;
	mlx->map.columns = 0;
	fd = open(filepath, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (mlx->map.lines == 0)
			mlx->map.columns = count_numbers(line);
		else if (mlx->map.columns != count_numbers(line))
		{
			printf("map.columns: %d\n", mlx->map.columns);
			printf("count_numbers(line): %d\n", count_numbers(line));
			return (free(line), 0);
		}
		mlx->map.lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	count_numbers(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ' || line[i] == '-')
			i++;
		if (line[i] && ft_isdigit(line[i]))
			count++;
		while (line[i] && line[i] != ' ')
			i++;
	}
	return (count);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->numbers[i])
	{
		free(map->numbers[i]);
		i++;
	}
	free(map->numbers);
	map->numbers = NULL;
}
