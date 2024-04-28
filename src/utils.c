/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:27:33 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/28 18:02:15 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	print_error(char *msg)
{
	printf(RED "%s" RST "\n", msg);
	exit(EXIT_FAILURE);
}

long	get_time(int time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		print_error("Error when try to Gettimeofday");
	if (MILLISEC == time_code)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else if (MICROSEC == time_code)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else
		return (print_error("Wrong input to gettime"));
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed_time;
	long	remained;

	start = get_time(MICROSEC);
	while (get_time(MICROSEC) - start < usec)
	{
		if (end_simulation(table))
			break ;
		elapsed_time = get_time(MICROSEC) - start;
		remained = usec - elapsed_time;
		if (remained > 1e3)
			usleep(remained / 2);
		else
			while (get_time(MICROSEC) - start < usec)
				;
	}
}

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISEC) - philo->table->start_simulation;
	if (philo->full)
		return ;
	mutex_handle(&philo->table->write_mutex, LOCK);
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& !end_simulation(philo->table))
		printf(W "%-6ld" RST " %d has taken a fork 🍽\n", elapsed, philo->id);
	else if (EATING == status && !end_simulation(philo->table))
		printf(W "%-6ld" RST " %d is eating 🍝\n" RST, elapsed, philo->id);
	else if (SLEEPING == status && !end_simulation(philo->table))
		printf(W "%-6ld" RST " %d is sleeping 😴\n", elapsed, philo->id);
	else if (THINKING == status && !end_simulation(philo->table))
		printf(W "%-6ld" RST " %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED "%-6ld %d 💀💀 died 💀💀\n" RST, elapsed, philo->id);
	mutex_handle(&philo->table->write_mutex, UNLOCK);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->nb_philos)
	{
		philo = table->philos + i;
		mutex_handle(&philo->philo_mutex, DESTROY);
	}
	mutex_handle(&table->write_mutex, DESTROY);
	mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
