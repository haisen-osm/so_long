/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:09:28 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/15 14:43:02 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mlx.h>

#define EXTENSTION ".ber"
#  define BUFFER_SIZE 13370
// get_next_line functions
char	*get_next_line(int fd);
void	*free_resources(char **saved_data, char **read_buffer);
char	*read_and_store(int fd, char *saved_data, char *read_buffer);
char	*extract_line_to_return(char *saved_data, char *line_to_return);
char	*trim_saved_data(char *saved_data);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dest, const char *src);
#endif