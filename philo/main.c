/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 02:38:18 by gabdoush          #+#    #+#             */
/*   Updated: 2022/06/02 12:19:19 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*============================================================================*/
int	main(int argc, char **argv)
{
	t_pro_d	pro_d;

	pro_d.start_time = action_time();
	if (argc < 4)
	{
		ft_putstr_fd("Wrong arguments, Enter (4) argument to start.\n", 2);
		return (0);
	}
	else if (argc == 5 || argc == 6)
	{
		if (!parse_args(argv))
			return (0);
		move_to_struct(argv, &pro_d);
		if (!philosopher(&pro_d))
			return (0);
		destroy_free(&pro_d);
	}
	else
	{
		ft_putstr_fd("Wrong arguments number, Enter (4) arguments only.\n", 2);
		return (0);
	}
	return (EXIT_SUCCESS);
}

/*============================================================================*/