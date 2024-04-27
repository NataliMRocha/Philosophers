/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoreir <namoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:57:27 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/27 17:57:42 by namoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	handle_error_mutex(int status, t_opcode op)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (LOCK == op || UNLOCK == op))
		print_error("The value specified by mutex is invalid");
	else if(EINVAL == status && INIT == op)
		print_error("The value specified by attr is invalid");
	else if(EDEADLK == status)
		print_error("A deadlock would occur if the thread blocked waiting for mutex");
	else if(EPERM == status)
		print_error("The current thread does not hold a lock on mutex");
	else if(EBUSY == status)
		print_error("Mutex is locked");
}

void	mutex_handle(t_mtx *mutex, t_opcode op)
{
	if(LOCK == op)
		handle_error_mutex(pthread_mutex_lock(mutex), op);
	else if(UNLOCK == op)
		handle_error_mutex(pthread_mutex_unlock(mutex), op);
	else if(INIT == op)
		handle_error_mutex(pthread_mutex_init(mutex, NULL), op);
	else if(DESTROY == op)
		handle_error_mutex(pthread_mutex_destroy(mutex), op);
	else
		print_error("wrong opcode for mutex handle");
}

static void	handle_thread_error(int status, t_opcode op)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("No resources to create another thread");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate permission\n");
	else if (EINVAL == status && CREATE == op)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == op || DETACH == op))
		error_exit("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread.");
}

void	thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode op)
{
	if (CREATE == op)
		handle_thread_error(pthread_create(thread, NULL, foo, data), op);
	else if (JOIN == op)
		handle_thread_error(pthread_join(*thread, NULL), op);
	else if (DETACH == op)
		handle_thread_error(pthread_detach(*thread), op);
	else
		error_exit("Wrong opcode for thread_handle:"
			" use <CREATE> <JOIN> <DETACH>");
}