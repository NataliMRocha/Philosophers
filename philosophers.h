/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoreir <namoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:16:35 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/26 16:44:39 by namoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "./libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_table	t_table;
// FORK
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int	fork_id;
}	t_fork;

// PHILO
typedef struct s_philo
{
	pthread_t	t_id;
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork *left_fork;
	t_fork *right_fork;
	t_table *table;
}	t_philo;

// TABLE
typedef struct s_table
{
	t_philo *philos;
	t_fork	*forks;
	long	philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat;
	long	start_simulation;
	bool	end_simulation;
	
}	t_table;

#endif