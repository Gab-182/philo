/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:42:00 by gabdoush          #+#    #+#             */
/*   Updated: 2022/06/11 13:06:39 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

/*----------------* MAX NUMS *----------------*/
# define MAX_PHILO_N 200
# define MIN_EAT_T 60
# define MIN_DIE_T 60
# define MIN_THINK_T 60
# define MIN_SLEEP_T 60

/*----------------* COLORES *-----------------*/
# define R "\033[0;31m"
# define G "\033[0;32m"
# define Y "\033[0;33m"
# define B "\033[0;34m"
# define P "\033[0;35m"
# define RESET "\033[0m"
/*============================  STRUCTURE  ===================================*/

/*---------------------   Philosopher Data   ---------------------------------*/
typedef struct s_ph_d
{
	struct s_pro_d	*pro_d;
	unsigned int	last_eating;
	int				philo_pos;
	int				left_fork;
	int				right_fork;
	int				req_meals;
	int				meals;
}			t_ph_d;

/*-----------------------   Program Data   -----------------------------------*/
typedef struct s_pro_d
{
	pthread_mutex_t			*forks;
	pthread_mutex_t			*printing_mutex;
	pthread_t				*philo_thread;
	pthread_mutex_t			*death;
	t_ph_d					*ph_d;
	int						philos_num;
	unsigned int			time_to_die;
	unsigned int			time_to_eat;
	unsigned int			time_to_sleep;
	unsigned int			start_time;
	int						meals_to_eat;
	int						*forks_state;
	pthread_mutex_t			*greedy_mutex;
	int						*greedy_forks;
	int						stop;
}			t_pro_d;

/*============================================================================*/

/*-------------------   philo_utils_libft.c   --------------------------------*/
int				ft_isdigit(int n);
void			ft_bzero(void *dest, size_t len);
void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);
void			ft_putstr_fd(char *s, int fd);

/*----------------------   philo_utils.c   -----------------------------------*/
void			usleep_pro(unsigned int time_to_delay, t_ph_d *ph_d);
unsigned int	action_time(void);
void			destroy_free(t_pro_d *pro_d);
void			printing_state(t_ph_d *ph_d, char *state, char *color);
void			handle_greedy_philo_eat(t_ph_d *ph_d);

/*-------------------------   philo.c   --------------------------------------*/
int				philosopher(t_pro_d *pro_d);

/*--------------------   parse_arguments.c   ---------------------------------*/
int				parse_args(char **argv);
void			move_to_struct(char **argv, t_pro_d *pro_d);

/*------------------------   eating.c   --------------------------------------*/
int				eating(t_ph_d *ph_d);
int				return_forks(t_ph_d *ph_d);
/*------------------------   action.c   --------------------------------------*/
int				after_eating_sleeping_thinking(t_ph_d *ph_d);

/*---------------------   philo_routine.c   ----------------------------------*/
int				check_greedy_even(t_ph_d *ph_d);
int				check_greedy_odd(t_ph_d *ph_d);
int				still_alive(t_ph_d *ph_d);
int				sleeping_thinking(t_ph_d *ph_d);
void			*philo_routine(void *arg);

/*============================================================================*/

#endif
