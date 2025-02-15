/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:37:33 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/15 14:37:43 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*ft_strdup(const char *s)
{
	char	*copy;

	if (!s)
		return (NULL);
	copy = malloc(ft_strlen(s) + 1);
	if (!copy)
		return (NULL);
	ft_strcpy(copy, s);
	return (copy);
}