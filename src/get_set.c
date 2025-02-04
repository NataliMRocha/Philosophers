/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:52:05 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/28 17:52:04 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	set_bool(t_mtx *mutex, bool *dst, bool value)
{
	mutex_handle(mutex, LOCK);
	*dst = value;
	mutex_handle(mutex, UNLOCK);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	mutex_handle(mutex, LOCK);
	ret = *value;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	mutex_handle(mutex, LOCK);
	ret = *value;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

bool	end_simulation(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
