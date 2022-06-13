/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:35:53 by gabdoush          #+#    #+#             */
/*   Updated: 2022/06/13 10:36:58 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*============================================================================*/
/**
 * @brief check if the argument in the main function is just numbers.
 * 
 * @param str 
 */
static int	check_if_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr_fd("Wrong arguments, Use just Unsigned integers.\n", 2);
		return (0);
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
		{
			ft_putstr_fd("Wrong arguments, Use just Unsigned integers.\n", 2);
			return (0);
		}
	}
	return (1);
}

/*============================================================================*/
/**
 * @brief Check the validaty of the main arguments.
 * 
 * @param argv
 */
static int	check_valid_integer(char **argv)
{
	if (ft_atoi(argv[1]) > MAX_PHILO_N || ft_atoi(argv[1]) < 1)
	{
		ft_putstr_fd("Wrong arguments, philosopher number is wrong.\n", 2);
		return (0);
	}
	if (ft_atoi(argv[1]) == 1)
	{
		ft_putstr_fd("philo 1 has Died, there is just one fork\n", 2);
		return (0);
	}
	if (ft_atoi(argv[2]) < MIN_DIE_T)
	{
		ft_putstr_fd("Wrong arguments, Dying time is too small.\n", 2);
		return (0);
	}
	if (ft_atoi(argv[4]) < MIN_SLEEP_T || ft_atoi(argv[3]) < MIN_EAT_T)
	{
		ft_putstr_fd("Wrong arguments, Wrong time.\n", 2);
		return (0);
	}
	return (1);
}

/*============================================================================*/
int	parse_args(char **argv)
{
	int	i;

	i = 1;
	while (argv && argv[i])
	{
		if (check_if_number(argv[i]) == 0)
			return (0);
		i++;
	}
	if (check_valid_integer(argv) == 0)
		return (0);
	return (1);
}

/*============================================================================*/
void	move_to_struct(char **argv, t_pro_d *pro_d)
{
	pro_d->philos_num = ft_atoi(argv[1]);
	pro_d->time_to_die = ft_atoi(argv[2]);
	pro_d->time_to_eat = ft_atoi(argv[3]);
	pro_d->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
			pro_d->meals_to_eat = ft_atoi(argv[5]);
	else
		pro_d->meals_to_eat = -1;
}

/*============================================================================*/