/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:21:15 by okhourss          #+#    #+#             */
/*   Updated: 2025/02/27 23:21:16 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_putnbr(int n)
{
	long	num;

	num = n;
	if (num > 9)
		ft_putnbr(num / 10);
	ft_putchar(num % 10 + 48);
}
