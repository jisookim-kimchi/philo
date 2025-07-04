/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokim2 <jisokim2@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:35:33 by jisokim2          #+#    #+#             */
/*   Updated: 2025/06/22 14:45:31 by jisokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isspace(char c)
{
	if (c == '\t' || c == '\r' || c == '\f'
		|| c == '\v' || c == '\n' || c == ' ')
		return (true);
	return (false);
}

static bool	ft_isdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (true);
	return (false);
}

static bool	is_num_args(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	ft_atoi(char *str)
{
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + *str - '0';
		str++;
	}
	if ((sign == 1 && result > INT_MAX)
		|| (sign == -1 && result < INT_MIN))
		return (ERROR);
	return ((int)(result * sign));
}

bool	is_valid(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (false);
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (false);
		i++;
	}
	if (!is_num_args(av + 1))
		return (false);
	return (true);
}
