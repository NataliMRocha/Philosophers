/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:56:11 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/28 17:57:17 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	forks_distribution(t_philo *philo, t_fork *fork, int pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->nb_philos;
	philo->left_fork = &fork[(pos + 1) % philo_nbr];
	philo->right_fork = &fork[pos];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &fork[pos];
		philo->right_fork = &fork[(pos + 1) % philo_nbr];
	}
}

static void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->nb_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		mutex_handle(&philo->philo_mutex, INIT);
		forks_distribution(philo, table->forks, i);
	}
}

void	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_thr_ready = false;
	table->threads_running_nbr = 0;
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (table->philos == NULL)
		print_error("malloc error");
	table->forks = malloc(sizeof(t_fork) * table->nb_philos);
	if (table->forks == NULL)
		print_error("malloc error");
	mutex_handle(&table->table_mutex, INIT);
	mutex_handle(&table->write_mutex, INIT);
	while (++i < table->nb_philos)
	{
		mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	init_philo(table);
}
