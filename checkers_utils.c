/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:49:54 by okhourss          #+#    #+#             */
/*   Updated: 2025/03/07 21:54:17 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_line(char *str, t_map *map, int is_first)
{
	int	len;
	int	current_len;

	len = ft_strlen(str);
	if (len == 1 && str[0] == '\n')
		exit_error(ERR_EMPTY_LINE, 0, str, NULL);
	if (str[len - 1] == '\n')
		current_len = len - 1;
	else
		current_len = len;
	if (map->rows == 0)
		map->cols = current_len;
	else if (map->cols != current_len)
		map->is_valid = 0;
	check_borders(str, map, is_first, 0);
	check_player_and_coins(str, map);
}

void	check_last_line(char *last_line, t_map *map)
{
	if (last_line)
	{
		check_borders(last_line, map, 0, 1);
		free(last_line);
	}
}
