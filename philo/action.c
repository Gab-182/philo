/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:28:32 by gabdoush          #+#    #+#             */
/*   Updated: 2022/06/11 12:36:21 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*============================================================================*/
int	after_eating_sleeping_thinking(t_ph_d *ph_d)
{
	if (!still_alive(ph_d))
		return (0);
	return_forks(ph_d);
	if (!still_alive(ph_d))
		return (0);
	if (!sleeping_thinking(ph_d))
		return (0);
	if (!still_alive(ph_d))
		return (0);
	return (1);
}

/*============================================================================*/