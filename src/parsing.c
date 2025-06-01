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
	if (ac != 5 && ac != 6)
		return (false);
	if (!is_num_args(av + 1))
		return (false);
	return (true);
}
