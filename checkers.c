/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:05:49 by okhourss          #+#    #+#             */
/*   Updated: 2025/03/01 13:17:38 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_extension(char *path)
{
	int len;
	int i;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strcmp(path + len - 4, ".ber") != 0)
		return (0);
	i = len - 5;
	while (i >= 0)
	{
		if (path[i] == '/')
			return (i < len - 5);
		i--;
	}
	return (1);
}

void check_borders(char *str, t_map *map, int is_first, int is_last)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if ((is_first || is_last) && str[i] != '1')
			map->is_valid = 0;
		else if ((i == 0 || i == map->cols - 1) && str[i] != '1')
			map->is_valid = 0;
		i++;
	}
}

void check_player_and_coins(char *str, t_map *map)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == 'P')
			map->player++;
		else if (str[i] == 'C')
			map->coin++;
		else if (str[i] == 'E')
			map->exit_door++;
		else if (str[i] != '0' && str[i] != '1')
			map->extra_char++;
		i++;
	}
}

void check_arguments(int argc, char *argv[])
{
	if (argc != 2)
		exit_error(ERR_ARGS, 0, NULL, NULL);
	if (!check_extension(argv[1]))
		exit_error(ERR_EXT, 0, NULL, NULL);
}

void validate_line(char *str, t_map *map, int is_first)
{
	int len;
	int current_len;

	len = ft_strlen(str);
	if (len == 1 && str[0] == '\n')
		exit_error(ERR_EMPTY_LINE, 0, str, NULL);
	current_len = (str[len - 1] == '\n') ? len - 1 : len;
	if (map->rows == 0)
		map->cols = current_len;
	else if (map->cols != current_len)
		map->is_valid = 0;
	check_borders(str, map, is_first, 0);
	check_player_and_coins(str, map);
}

void check_last_line(char *last_line, t_map *map)
{
	if (last_line)
	{
		check_borders(last_line, map, 0, 1);
		free(last_line);
	}
}

void check_map(t_map *map, int fd)
{
	char *str;
	char *last_line;
	int i;

	i = 0;
	last_line = NULL;
	str = get_next_line(fd);
	while (str != NULL)
	{
		validate_line(str, map, (i == 0));
		if (last_line)
			free(last_line);
		last_line = ft_strdup(str);
		free(str);
		map->rows++;
		i++;
		str = get_next_line(fd);
	}
	check_last_line(last_line, map);
}
