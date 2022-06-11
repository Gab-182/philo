/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 06:14:28 by gabdoush          #+#    #+#             */
/*   Updated: 2022/06/11 13:07:52 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_greedy_even(t_ph_d *ph_d)
{
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
	if (ph_d->pro_d->greedy_forks[ph_d->left_fork] == ph_d->philo_pos
		|| ph_d->pro_d->greedy_forks[ph_d->right_fork] == ph_d->philo_pos)
	{
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
		return (1);
	}
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
	return (0);
}

/*============================================================================*/
int	check_greedy_odd(t_ph_d *ph_d)
{
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
	if (ph_d->pro_d->greedy_forks[ph_d->left_fork] == ph_d->philo_pos
		|| ph_d->pro_d->greedy_forks[ph_d->right_fork] == ph_d->philo_pos)
	{
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
	return (0);
}

/*============================================================================*/
/**
 * @brief Check if any body has died, or if the philosopher is going to die.
 * 
 * @param ph_d 
 * @return int 
 */
int	still_alive(t_ph_d *ph_d)
{
	unsigned int	from_last_meal;

	pthread_mutex_lock(ph_d->pro_d->death);
	if (ph_d->pro_d->stop != 0 || ph_d->meals == ph_d->req_meals)
	{
		pthread_mutex_unlock(ph_d->pro_d->death);
		return (0);
	}
	pthread_mutex_unlock(ph_d->pro_d->death);
	from_last_meal = action_time() - ph_d->last_eating;
	pthread_mutex_lock(ph_d->pro_d->death);
	if (from_last_meal >= ph_d->pro_d->time_to_die
		&& ph_d->pro_d->stop == 0)
	{
		printing_state(ph_d, ": died Xx*___💀💀💀___*xX", R);
		ph_d->pro_d->stop = 1;
		pthread_mutex_unlock(ph_d->pro_d->death);
		return (0);
	}
	pthread_mutex_unlock(ph_d->pro_d->death);
	return (1);
}

/*============================================================================*/
/**
 * @brief Excute sleeping then thinking only after eating.
 * 
 * @param ph_d 
 * @return int 
 */
int	sleeping_thinking(t_ph_d *ph_d)
{
	if (!still_alive(ph_d))
		return (0);
	printing_state(ph_d, ": is sleeping 💤", B);
	usleep_pro(ph_d->pro_d->time_to_sleep, ph_d);
	if (!still_alive(ph_d))
		return (0);
	printing_state(ph_d, ": is thinking 🧠", P);
	return (1);
}

/*============================================================================*/
/**
 * @brief The routine function for each philosopher thread must follow.
 * 
 * @param arg 
 */
void	*philo_routine(void *arg)
{
	t_ph_d	*ph_d;

	ph_d = (t_ph_d *)arg;
	ph_d->last_eating = action_time();
	while (ph_d->meals != ph_d->req_meals)
	{
		pthread_mutex_lock(ph_d->pro_d->death);
		if (!ph_d->pro_d->stop)
		{
			pthread_mutex_unlock(ph_d->pro_d->death);
			if (!eating(ph_d))
				return (NULL);
		}
		else
		{
			pthread_mutex_unlock(ph_d->pro_d->death);
			return (NULL);
		}
	}
	return (arg);
}

/*============================================================================*/