#include "philo.h"

int	main(int ac, char **av)
{
	t_rules	rules;
	int	i;

	if (init_all(&rules, argc, argv))
		return (1);
	i = 0;
	while (i < rules.nb_philo)
	{
		if (pthread_create(&rules.philos[i].thread, NULL. philo_thread, &rules.philos[i]))
		{
			printf("Failed to create thread\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < rules.nb_philo)
	{
		pthread_join(rules.philos[i].thread, NULL);
		i++;
	}
	return (0);
}
