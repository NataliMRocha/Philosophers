/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoreir <namoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:56:11 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/27 18:13:54 by namoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	forks_distribution(t_philo *philo, t_fork *forks,
		int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->nb_philos;
	philo->left_fork = &forks[(philo_pos + 1) % philo_nbr];
	philo->right_fork = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[philo_pos];
		philo->right_fork = &forks[(philo_pos + 1) % philo_nbr];
	}	
}

static void init_philo(t_table *table)
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
		mutex_handle(&philo->philo_mutex, INIT);
		philo->table = table;
		forks_distribution(philo, table->forks, i);
	}
}

void init_table(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_thr_ready = false;
	table->threads_running_nbr = 0;
	table->nb_philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (table->nb_philos == NULL)
		print_error("malloc error");
	table->forks = malloc(sizeof(sizeof(t_philo) * table->nb_philos));
	if (table->forks == NULL)
		print_error("malloc error");
	mutex_handle(&table->table_mutex, INIT);
	mutex_handle(&table->write_mutex, INIT);
	while(++i < table->nb_philos)
	{
		mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	init_philo(table);
}