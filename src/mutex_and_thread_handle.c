/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_and_thread_handle.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:57:27 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/28 17:55:37 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	handle_error_mutex(int status, t_opcode op)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (LOCK == op || UNLOCK == op))
		print_error("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == op)
		print_error("The value specified by attr is invalid");
	else if (EDEADLK == status)
		print_error("A deadlock would occur if"
			"the thread blocked waiting for mutex");
	else if (EPERM == status)
		print_error("The current thread does not hold a lock on mutex");
	else if (ENOMEM == status)
		print_error("Memory is not enough to create another mutex");
	else if (EBUSY == status)
		print_error("Mutex is locked");
}

void	mutex_handle(t_mtx *mutex, t_opcode op)
{
	if (INIT == op)
		handle_error_mutex(pthread_mutex_init(mutex, NULL), op);
	else if (LOCK == op)
		handle_error_mutex(pthread_mutex_lock(mutex), op);
	else if (UNLOCK == op)
		handle_error_mutex(pthread_mutex_unlock(mutex), op);
	else if (DESTROY == op)
		handle_error_mutex(pthread_mutex_destroy(mutex), op);
	else
		print_error("Invalid op code");
}

static void	handle_thread_error(int status, t_opcode op)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		print_error("No resources to create another thread");
	else if (EPERM == status)
		print_error("The caller does not have appropriate permission");
	else if (EINVAL == status && CREATE == op)
		print_error("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == op || DETACH == op))
		print_error("The value specified by thread is not joinable");
	else if (ESRCH == status)
		print_error("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		print_error("A deadlock was detected or the value of"
			"thread specifies the calling thread.");
}

void	thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode op)
{
	if (CREATE == op)
		handle_thread_error(pthread_create(thread, NULL, foo, data), op);
	else if (JOIN == op)
		handle_thread_error(pthread_join(*thread, NULL), op);
	else if (DETACH == op)
		handle_thread_error(pthread_detach(*thread), op);
	else
		print_error("Wrong opcode for thread_handle");
}
