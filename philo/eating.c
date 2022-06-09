/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 04:45:35 by gabdoush          #+#    #+#             */
/*   Updated: 2022/06/08 20:46:52 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*============================================================================*/
static void	start_eating(t_ph_d *ph_d, int flag)
{
	ph_d->pro_d->forks_state[ph_d->right_fork] = ph_d->philo_pos;
	ph_d->pro_d->forks_state[ph_d->left_fork] = ph_d->philo_pos;
	printing_state(ph_d, ": has taken a fork 🍴", Y);
	printing_state(ph_d, ": has taken a fork 🍴🍴", Y);
	printing_state(ph_d, ": is eating 🍝", G);
	if (flag == 1)
	{
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
	}
	else if (flag == 2)
	{
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
	}
	ph_d->last_eating = action_time();
	usleep_pro(ph_d->pro_d->time_to_eat);
	ph_d->meals++;
}

/*============================================================================*/
static void	return_forks(t_ph_d *ph_d)
{
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
	ph_d->pro_d->forks_state[ph_d->left_fork] = 0;
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
	ph_d->pro_d->forks_state[ph_d->right_fork] = 0;
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
}

/*============================================================================*/
static int	one_way(t_ph_d *ph_d)
{
	if (!still_alive(ph_d))
		return (0);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
	if (ph_d->pro_d->forks_state[ph_d->right_fork] == 0
		&& ph_d->pro_d->forks_state[ph_d->left_fork] == 0)
	{
		start_eating(ph_d, 1);
		return_forks(ph_d);
		if (!sleeping_thinking(ph_d))
			return (0);
	}
	else
	{
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
		if (!still_alive(ph_d))
			return (0);
	}
	return (1);
}

/*============================================================================*/
static int	other_way(t_ph_d *ph_d)
{
	if (!still_alive(ph_d))
		return (0);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
	if (ph_d->pro_d->forks_state[ph_d->right_fork] == 0
		&& ph_d->pro_d->forks_state[ph_d->left_fork] == 0)
	{
		start_eating(ph_d, 2);
		return_forks(ph_d);
		if (!sleeping_thinking(ph_d))
			return (0);
	}
	else
	{
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
		if (!still_alive(ph_d))
			return (0);
	}
	return (1);
}

/*============================================================================*/
int	eating(t_ph_d *ph_d)
{
	if (!still_alive(ph_d))
		return (0);
	if (ph_d->philo_pos % 2 != 0)
	{
		if (one_way(ph_d))
			return (1);
	}
	else
	{
		if (other_way(ph_d))
			return (1);
	}
	return (0);
}

/*============================================================================*/