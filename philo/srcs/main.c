/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:16:01 by hrecolet          #+#    #+#             */
/*   Updated: 2022/03/01 13:20:18 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_dead_message(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->dead_m);
	printf("%d %d died\n", get_time() - philo->var->start, philo->id);
	philo->var->is_dead = 1;
	pthread_mutex_unlock(&philo->var->dead_m);
}

int	kill_philo(t_philo *philo)
{
	if (get_time() - philo->var->start > philo->wdie)
	{
		philo_dead_message(philo);
		pthread_mutex_unlock(&philo->var->mutex);
		return (1);
	}
	return (0);
}

void	*routine(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (philo->var->is_dead == 0)
	{
		if (ft_is_dead(philo))
			return (0);
		take_forks(philo);
		if (ft_is_dead(philo))
		{
			pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(philo->lfork);
			return (0);
		}
		eat(philo);
		if (ft_is_dead(philo))
			return (0);
		sleeping(philo);
		if (ft_is_dead(philo))
			return (0);
		think(philo);
		usleep(200);
	}
	return (0);
}

void	*monitor(void *var_v, int i, int nb_philo_count)
{
	t_vars	*var;

	var = (t_vars *)var_v;
	while (1)
	{
		i = -1;
		while (++i < var->nb_philo)
		{
			pthread_mutex_lock(&var->mutex);
			if (var->philos[i].count == var->amount_loop)
			{
				nb_philo_count++;
				var->philos[i].count = -1;
				if (nb_philo_count == var->nb_philo)
				{
					var->is_dead = 1;
					return (pthread_mutex_unlock(&var->mutex), NULL);
				}
			}
			if (kill_philo(&var->philos[i]))
				return (NULL);
			pthread_mutex_unlock(&var->mutex);
		}
		usleep(200);
	}
}

int	main(int ac, char **av)
{
	t_vars	var;

	if (ac < 5 || ac > 6)
	{
		write(1, "Wrong number of arguments (5 || 6)\n", 35);
		return (0);
	}
	if (check_args(av))
		return (0);
	if (init_vars(&var, av))
		return (0);
	if (check_data(&var))
	{
		ft_free_data(&var);
		return (0);
	}
	if (init_threads(&var))
	{
		ft_free_data(&var);
		return (0);
	}
	join_thread(&var);
	ft_free_data(&var);
	return (0);
}
