#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		result;

	if (init_simulation(ac, av, &table))
		return (1);
	result = start_simulation(&table);
	cleanup_table(&table);
	return (result);
}
