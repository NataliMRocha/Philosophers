/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:28:27 by natali            #+#    #+#             */
/*   Updated: 2024/04/28 17:52:13 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	die_time;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISEC) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	die_time = philo->table->time_to_die / 1e3;
	if (elapsed > die_time)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->nb_philos))
		;
	while (!end_simulation(table))
	{
		i = -1;
		while (++i < table->nb_philos && !end_simulation(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
