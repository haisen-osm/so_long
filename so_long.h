/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:09:28 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/18 21:49:42 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
// #include <mlx.h>

typedef struct s_map
{
	size_t rows;
	size_t cols;
	int is_valid;
	int player;
	int coin;
	int exitDor;
	int extra_char;
	char **grid;
	char **grid_copy;
} t_map;

#define EXTENSTION ".ber"
#define ERR_ARGS "Invalid number of arguments."
#define ERR_EXT "Wrong file extension."
#define ERR_OPEN "Failed to open the file. "
#define ERR_EMPTY_LINE "Empty line in the map."
#define ERR_INVALID_MAP "Invalid map structure."
#define ERR_NOT_REACHABLE "can't reach all the colaictables"
#define BUFFER_SIZE 1370
// get_next_line functions
char *get_next_line(int fd);
void *free_resources(char **saved_data, char **read_buffer);
char *read_and_store(int fd, char *saved_data, char *read_buffer);
char *extract_line_to_return(char *saved_data, char *line_to_return);
char *trim_saved_data(char *saved_data);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s);
char *ft_strjoin(char *s1, char *s2);
char *ft_strchr(const char *s, int c);
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(char *s1, char *s2);

#endif