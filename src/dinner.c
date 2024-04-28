/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:32:26 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/28 17:51:58 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISEC));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!end_simulation(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo);
	if (philo->table->nb_philos % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

static void	eating(t_philo *philo)
{
	mutex_handle(&philo->left_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	mutex_handle(&philo->right_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISEC));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->must_eat > 0
		&& philo->meals_counter == philo->table->must_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
}

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISEC));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	unsync(philo);
	while (!end_simulation(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eating(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->must_eat)
		return ;
	else if (1 == table->nb_philos)
		thread_handle(&table->philos[0].t_id, one_philo, &table->philos[0],
			CREATE);
	else
		while (++i < table->nb_philos)
			thread_handle(&table->philos[i].t_id, dinner_simulation,
				&table->philos[i], CREATE);
	thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = get_time(MILLISEC);
	set_bool(&table->table_mutex, &table->all_thr_ready, true);
	i = -1;
	while (++i < table->nb_philos)
		thread_handle(&table->philos[i].t_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	thread_handle(&table->monitor, NULL, NULL, JOIN);
}
