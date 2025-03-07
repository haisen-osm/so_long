/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:33:14 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/28 17:20:40 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**grid_map(int rows, int fd)
{
	char	*str;
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (rows + 1));
	if (!arr)
		exit_error("Malloc allocation failed\n", 0, 0, 0);
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
		exit_error("Malloc failed\n", 0, NULL, grid);
	i = 0;
	while (i < rows)
	{
		copy[i] = (char *)malloc(sizeof(char) * (ft_strlen(grid[i]) + 1));
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			exit_error("Malloc failed\n", 0, NULL, grid);
		}
		ft_strcpy(copy[i], grid[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	validate_map(t_map *map, int fd)
{
	t_flood	flood;

	find_player(map, &flood.row, &flood.col);
	flood.exit_found = 0;
	flood.coin_found = 0;
	flood_fill(map, &flood, flood.col, flood.row);
	free_2dmap(map->grid_copy);
	if (flood.coin_found != map->coin || flood.exit_found != 1)
	{
		close(fd);
		exit_error(ERR_NOT_REACHABLE, 0, NULL, map->grid);
	}
}

void	ft_parsing(t_map *map, int argc, char **argv)
{
	int	fd;

	check_arguments(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error(ERR_OPEN, NULL, NULL, NULL);
	initialize_map(map);
	check_map(map, fd);
	close(fd);
	if (map->rows < 3 || map->cols < 3)
		exit_error(ERR_INVALID_MAP, 0, NULL, NULL);
	if (!map->is_valid)
		exit_error(ERR_INVALID_MAP, 0, NULL, NULL);
	if (map->player != 1 || map->coin == 0 || map->exit_door != 1
		|| map->extra_char > 0)
		exit_error(ERR_INVALID_MAP, 0, NULL, NULL);
	if ((map->rows * 64) > 2160 || (map->cols * 64) > 3840)
		exit_error("Map size bigger than screen size\n", 0, 0, 0);
	fd = open(argv[1], O_RDONLY);
	map->grid = grid_map(map->rows, fd);
	map->grid_copy = copy_map(map->grid, map->rows, map->cols);
	find_door(map);
	validate_map(map, fd);
	close(fd);
}
