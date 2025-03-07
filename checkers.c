/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:05:49 by okhourss          #+#    #+#             */
/*   Updated: 2025/03/07 21:50:37 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_extension(char *path)
{
	int	len;
	int	i;

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

void	check_borders(char *str, t_map *map, int is_first, int is_last)
{
	int	i;

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

void	check_player_and_coins(char *str, t_map *map)
{
	int	i;

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

void	check_arguments(int argc, char *argv[])
{
	if (argc != 2)
		exit_error(ERR_ARGS, 0, NULL, NULL);
	if (!check_extension(argv[1]))
		exit_error(ERR_EXT, 0, NULL, NULL);
}

void	check_map(t_map *map, int fd)
{
	char	*str;
	char	*last_line;
	int		i;

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
