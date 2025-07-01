/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:10:07 by mohel-am          #+#    #+#             */
/*   Updated: 2025/07/01 18:10:09 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (init_simulation(ac, av, &table))
		return (1);
	if (start_simulation(&table))
		return (1);
	//end_simulation(&table);
	return (0);
}
