/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:33:14 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/25 17:10:30 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**grid_map(int rows, int fd)
{
	char	*str;
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (rows + 1));
	i = 0;
	str = get_next_line(fd);
	while (i < rows && str != NULL)
	{
		arr[i] = str;
		i++;
		str = get_next_line(fd);
	}
	arr[i] = NULL;
	return (arr);
}

char	**copy_map(char **grid, size_t rows, size_t cols)
{
	char	**copy;
	size_t	i;

	(void)cols;
	copy = malloc(sizeof(char *) * (rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = (char *)malloc(sizeof(char) * (ft_strlen(grid[i]) + 1));
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		ft_strcpy(copy[i], grid[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	validate_map(t_map *map)
{
	int	exit_found;
	int	coin_found;
	int	row;
	int	col;

	find_player(map, &row, &col);
	exit_found = 0;
	coin_found = 0;
	flood_fill(map, row, col, map->grid_copy, &exit_found, &coin_found);
	if (coin_found != map->coin || exit_found != 1)
		exit_error(ERR_NOT_REACHABLE, 0);
}

void	ft_parsing(t_map *map, int argc, char **argv)
{
	int	fd;

	check_arguments(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error(ERR_OPEN, 1);
	initialize_map(map);
	check_map(map, fd);
	close(fd);
	if (map->rows < 3 || map->cols < 3)
		exit_error(ERR_INVALID_MAP, 0);
	if (!map->is_valid)
		exit_error(ERR_INVALID_MAP, 0);
	if (map->player != 1 || map->coin == 0 || map->exitDoor != 1
		|| map->extra_char > 0)
		exit_error(ERR_INVALID_MAP, 0);
	fd = open(argv[1], O_RDONLY);
	map->grid = grid_map(map->rows, fd);
	map->grid_copy = copy_map(map->grid, map->rows, map->cols);
	validate_map(map);
	close(fd);
}
