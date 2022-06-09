/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:42:08 by gabdoush          #+#    #+#             */
/*   Updated: 2022/06/08 17:39:24 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*============================================================================*/
/**
 * @brief Allocate memory for the philos array.
 * 		  Allocate memory for forks array.
 * 		  Allocate memory for each philosopher's data.
 * 
 * @param pro_d 
 */
static int	allocate_memory(t_pro_d *pro_d)
{
	pro_d->ph_d = malloc(sizeof(t_ph_d) * pro_d->philos_num);
	pro_d->philo_thread = malloc(sizeof(pthread_t) * pro_d->philos_num);
	pro_d->forks = malloc(sizeof(pthread_mutex_t) * pro_d->philos_num);
	pro_d->printing_mutex = malloc(sizeof(pthread_mutex_t));
	pro_d->death = malloc(sizeof(pthread_mutex_t));
	pro_d->forks_state = ft_calloc(sizeof(int), pro_d->philos_num);
	if (!pro_d->ph_d || !pro_d->philo_thread
		|| !pro_d->forks || !pro_d->printing_mutex
		|| !pro_d->death ||!pro_d->forks_state)
	{
		ft_putstr_fd("Allocation failed\n", 2);
		return (0);
	}
	return (1);
}

/*============================================================================*/
/**
 * @brief Initialize the mutexes for the forks and also the staes for the forks.
 * 
 * @param pro_d 
 */
static int	initialize_forks_mutexes(t_pro_d *pro_d)
{
	int	i;

	i = 0;
	while (i < pro_d->philos_num)
	{
		if (pthread_mutex_init(&pro_d->forks[i], NULL) != 0)
		{
			ft_putstr_fd("Error while initializing one of the mutexes\n", 2);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(pro_d->printing_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error while initializing one of the mutexes\n", 2);
		return (0);
	}
	if (pthread_mutex_init(pro_d->death, NULL) != 0)
	{
		ft_putstr_fd("Error while initializing one of the mutexes\n", 2);
		return (0);
	}
	return (1);
}

/*============================================================================*/
/**
 * @brief Just initialize the data for each philosopher thread.
 * 
 * @param ph_d 
 */
static void	init_philosophers_data(t_ph_d *ph_d, int i)
{
	ph_d->philo_pos = i + 1;
	ph_d->req_meals = ph_d->pro_d->meals_to_eat;
	ph_d->meals = 0;
	ph_d->left_fork = i;
	ph_d->right_fork = (i + 1) % ph_d->pro_d->philos_num;
}

/*============================================================================*/
/**
 * @brief Create a philo threads object according to the given first number
 * in the main parameters.
 * 
 * @param pro_d
 */
static int	create_philo_threads(t_pro_d *pro_d)
{
	int			i;

	i = 0;
	while (i < pro_d->philos_num)
	{
		pthread_create(&pro_d->philo_thread[i], NULL,
			philo_routine, (void *)&pro_d->ph_d[i]);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < pro_d->philos_num)
	{
		if (pthread_join(pro_d->philo_thread[i], NULL) != 0)
		{
			ft_putstr_fd("Error while joining the threads\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

/*============================================================================*/
/**
 * @brief The main function that excute each other function.
 * 
 * @param pro_d 
 * @return void 
 */
int	philosopher(t_pro_d *pro_d)
{
	int	i;

	i = 0;
	pro_d->stop = 0;
	allocate_memory(pro_d);
	if (!initialize_forks_mutexes(pro_d))
		return (0);
	while (i < pro_d->philos_num)
	{
		pro_d->ph_d[i].pro_d = pro_d;
		init_philosophers_data(&pro_d->ph_d[i], i);
		i++;
	}
	if (!create_philo_threads(pro_d))
		return (0);
	return (1);
}

/*============================================================================*/