/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:18:59 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/23 15:56:46 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			s;
	long int	j;

	i = 0;
	s = 1;
	j = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((j > INT_MAX / 10) || (j == INT_MAX / 10 && (nptr[i] - '0') > INT_MAX % 10))
		{
			if (s == 1)
				return (0);
			else
				return (-1);
		}
		j = (j * 10) + (nptr[i] - '0');
		i++;
	}
	return ((int)j * s);
}
