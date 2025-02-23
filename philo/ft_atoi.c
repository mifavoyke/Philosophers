/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:39:04 by yhusieva          #+#    #+#             */
/*   Updated: 2025/02/23 20:47:51 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	convert_number(const char *nptr, int *i, int s)
{
	long	j;

	j = 0;
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		if ((j > INT_MAX / 10)
			|| (j == INT_MAX / 10 && (nptr[*i] - '0') > INT_MAX % 10))
		{
			if (s == 1)
				return (0);
			else
				return (-1);
		}
		j = j * 10 + (nptr[*i] - '0');
		(*i)++;
	}
	if (nptr[*i] != '\0')
		return (-1);
	return ((int)j * s);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			s;

	i = 0;
	s = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s *= -1;
		i++;
	}
	return (convert_number(nptr, &i, s));
}
