/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:38:09 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/15 14:46:29 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	j;
	char	*new_str;

	if (!s1 || !s2)
	{
		free(s1);
		return (NULL);
	}
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	ft_strcpy(new_str, s1);
	j = 0;
	while (s2[j])
	{
		new_str[ft_strlen(s1) + j] = s2[j];
		j++;
	}
	new_str[ft_strlen(s1) + j] = '\0';
	free(s1);
	return (new_str);
}