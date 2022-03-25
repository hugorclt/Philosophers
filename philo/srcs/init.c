/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:29:03 by hrecolet          #+#    #+#             */
/*   Updated: 2022/03/01 14:25:14 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*only_one(void *av)
{
	char	**argv;

	argv = (char **)av;
	printf("%d %d has taken a fork\n", 0, 1);
	usleep(ft_atoi(argv[2]));
	printf("%d %d died\n", ft_atoi(argv[2]), 1);
	return (NULL);
}

int	init_mutex(t_vars *var)
{
	int	i;

	i = 0;
	var->fork_m = malloc(sizeof(pthread_mutex_t) * var->nb_philo);
	if (!var->fork_m)
		return (1);
	while (i < var->nb_philo)
	{
		pthread_mutex_init(&var->fork_m[i], NULL);
		i++;
	}
	pthread_mutex_init(&var->mutex, NULL);
	pthread_mutex_init(&var->dead_m, NULL);
	return (0);
}

int	init_philo(t_vars *var)
{
	int	i;

	i = 0;
	var->philos = malloc(sizeof(t_philo) * var->nb_philo);
	if (!var->philos)
		return (1);
	while (i < var->nb_philo)
	{
		var->philos[i].id = i + 1;
		var->philos[i].lfork = &var->fork_m[i];
		var->philos[i].rfork = &var->fork_m[(i + 1) % var->nb_philo];
		var->philos[i].var = var;
		var->philos[i].wdie = var->t_die;
		var->philos[i].last_eat = 0;
		var->philos[i].is_eating = 0;
		var->philos[i].wdie = var->t_die;
		var->philos[i].count = 0;
		i++;
	}
	return (0);
}

int	init_vars(t_vars *var, char **av)
{
	pthread_t	tid;

	if (ft_atoi(av[1]) == 1)
	{
		if (pthread_create(&tid, NULL, &only_one, av)
			!= 0)
			return (1);
		pthread_join(tid, NULL);
		return (1);
	}
	var->nb_philo = ft_atoi(av[1]);
	var->t_die = ft_atoi(av[2]);
	var->t_eat = ft_atoi(av[3]);
	var->t_sleep = ft_atoi(av[4]);
	var->is_dead = 0;
	if (av[5])
		var->amount_loop = ft_atoi(av[5]);
	else
		var->amount_loop = -1;
	if (init_mutex(var))
		return (1);
	if (init_philo(var))
		return (free(var->fork_m), 0);
	return (0);
}

int	init_threads(t_vars *var)
{
	int		i;
	void	*philo;

	i = -1;
	var->start = get_time();
	while (++i < var->nb_philo)
	{
		philo = (void *)(&var->philos[i]);
		if (i % 2 == 0)
			if (pthread_create(&var->philos[i].id_thread, NULL, &routine, philo)
				!= 0)
				return (1);
	}
	i = -1;
	usleep(10);
	while (++i < var->nb_philo)
	{
		philo = (void *)(&var->philos[i]);
		if (i % 2 == 1)
			if (pthread_create(&var->philos[i].id_thread, NULL, &routine, philo)
				!= 0)
				return (1);
	}
	monitor(var, 0, 0);
	return (0);
}
