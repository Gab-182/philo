/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:26:15 by gabdoush          #+#    #+#             */
/*   Updated: 2022/06/09 15:12:19 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_greedy_philo_eat(t_ph_d *ph_d)
{
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
	ph_d->pro_d->greedy_forks[ph_d->left_fork] = ph_d->philo_pos;
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
	ph_d->pro_d->greedy_forks[ph_d->right_fork] = ph_d->philo_pos;
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
}

/*============================================================================*/
void	printing_state(t_ph_d *ph_d, char *state, char *color)
{
	unsigned int	start_time;

	start_time = ph_d->pro_d->start_time;
	pthread_mutex_lock(ph_d->pro_d->printing_mutex);
	printf("%s\033[1m %d [%d] %s\n", color, (action_time() - start_time),
		ph_d->philo_pos, state);
	pthread_mutex_unlock(ph_d->pro_d->printing_mutex);
}

/*============================================================================*/
/**
 * @brief Delaing the time to excute an act depending on the time_to_delay.
 * 
 * @param time_to_delay 
 */
void	usleep_pro(unsigned int time_to_delay)
{
	unsigned int	now_time;

	now_time = action_time();
	while ((action_time() - now_time) < (time_to_delay))
		usleep(time_to_delay / 100);
}

/*============================================================================*/
/**
 * @brief Get the actual time to keep track of the philosopher threads.
 * 
 * @param start_time 
 * @return int 
 */
unsigned int	action_time(void)
{
	struct timeval	time;
	unsigned int	msec;

	gettimeofday(&time, NULL);
	msec = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (msec);
}

/*============================================================================*/
/**
 * @brief Destroy and free the forks mutexes, and the print mutex.
 * and free the threads
 * 
 * @param pro_d
 */
void	destroy_free(t_pro_d *pro_d)
{
	int	i;

	i = 0;
	while (i < pro_d->philos_num)
	{
		pthread_mutex_destroy(&pro_d->forks[i]);
		i++;
	}
	pthread_mutex_destroy(pro_d->printing_mutex);
	pthread_mutex_destroy(pro_d->death);
	free(pro_d->forks);
	free(pro_d->ph_d);
	free(pro_d->printing_mutex);
	free(pro_d->death);
	free(pro_d->forks_state);
	free(pro_d->philo_thread);
}

/*============================================================================*/