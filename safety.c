/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:31:36 by eagranat          #+#    #+#             */
/*   Updated: 2024/11/08 13:16:42 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *protect_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		print_error("Malloc failed.\n");
	return (ptr);
}

void safe_mutex(t_mtx *mtx, t_opcode opcode)
{
	if (opcode == LOCK)
		pthread_mutex_lock(mtx);
	else if (opcode == UNLOCK)
		pthread_mutex_unlock(mtx);
	else if (opcode == INIT)
		pthread_mutex_init(mtx, NULL);
	else if (opcode == DESTROY)
		pthread_mutex_destroy(mtx);
	else
		print_error("Invalid mutex opcode.\n");
}

static void handle_mutex_error(int status, t_opcode opcode)
{

	if (status == 0)
		return;
	if (status == EINVAL)
	{
		if (LOCK == opcode || UNLOCK == opcode)
			print_error("The mutex is not initialized.\n");
		else if (DESTROY == opcode)
			print_error("The mutex is already destroyed or invalid.\n");
		else if (CREATE == opcode || JOIN == opcode)
			print_error("The thread is not joinable.\n");
		else if (DETACH == opcode)
			print_error("The thread is already detached.\n");
	}
	else if (status == EBUSY && DESTROY == opcode)
		print_error("The mutex is currently locked and cannot be destroyed.\n");
	else if (status == EPERM && (LOCK == opcode || UNLOCK == opcode))
		print_error("Current thread does not own the mutex (unlocking).\n");
	else
		print_error("Unknown mutex or thread error.\n");
}

static void handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return;
	if (status == EAGAIN)
		print_error("No resources to create a new thread.\n");
	else if (status == EPERM)
		print_error("The caller does not have appropriate permissions");
	else if (status == EINVAL && opcode == CREATE)
		print_error("The value specified by attr is invalid.\n");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		print_error("The value specified by thread is not joinable.\n");
	else if (status == ESRCH)
		print_error("No thread could be found corresponding to that specified by the given thread ID.\n");
	else if (status == EDEADLK)
		print_error("A deadlock was detected or the value of thread specifies the calling thread.\n");
	else
		print_error("Unknown thread error.\n");
}

void safe_thread(pthread_t *thread, void (*foo)(void *), void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, (void *)foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		print_error("Invalid thread opcode.\n");
}
