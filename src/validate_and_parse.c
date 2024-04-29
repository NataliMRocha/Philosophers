/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_and_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoreir <namoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:22:04 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/29 11:41:29 by namoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	validation(char *argv)
{
	int	i;

	i = 0;
	while (is_space(argv[i]))
		i++;
	if (argv[i] == '+')
		i++;
	else if (argv[i] == '-')
		return (print_error("You can't use negative number\n"));
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (print_error("Invalid input, use only digits"));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_args(int argc, char **argv)
{
	long long int	arg;
	int				i;

	if (argc < 5)
		return (print_error("Usage: philos time_to_die time_to_eat"
				"time_to_sleep (optional)must_eat"));
	if (argc > 6)
		return (print_error("Too many arguments"));
	i = 1;
	while (argv[i])
	{
		arg = ft_atol(argv[i]);
		if (arg < 0)
			return (print_error("Invalid negative arg"));
		if (arg > INT_MAX)
			return (print_error("Can't be bigger than INT MAX"));
		validation(argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	parsing(t_table *table, char **argv)
{
	table->nb_philos = ft_atol(argv[1]);
	if (table->nb_philos > PHILO_MAX)
		table->nb_philos = PHILO_MAX;
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (argv[5])
		table->must_eat = ft_atol(argv[5]);
	else
		table->must_eat = -1;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		print_error("Use timestamps bigger than 60ms");
}
