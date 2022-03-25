/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:37:58 by hrecolet          #+#    #+#             */
/*   Updated: 2022/03/01 13:23:49 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->mutex);
	if (philo->var->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->var->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->var->mutex);
	return (0);
}

void	eat(t_philo *philo)
{
	display_message(philo, "is eating");
	pthread_mutex_lock(&philo->var->mutex);
	philo->last_eat = get_time() - philo->var->start;
	philo->wdie = philo->last_eat + philo->var->t_die;
	pthread_mutex_unlock(&philo->var->mutex);
	ft_usleep(philo->var->t_eat, philo);
	pthread_mutex_lock(&philo->var->mutex);
	if (philo->count > -1)
		philo->count++;
	pthread_mutex_unlock(&philo->var->mutex);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->rfork);
	else
		pthread_mutex_lock(philo->lfork);
	display_message(philo, "has taken a fork");
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->lfork) != 0)
		{
			pthread_mutex_unlock(philo->rfork);
			return (1);
		}
		display_message(philo, "has taken a fork");
	}
	else
	{
		if (pthread_mutex_lock(philo->rfork) != 0)
		{
			pthread_mutex_unlock(philo->lfork);
			return (1);
		}
		display_message(philo, "has taken a fork");
	}
	return (0);
}

void	sleeping(t_philo *philo)
{
	display_message(philo, "is sleeping");
	ft_usleep(philo->var->t_sleep, philo);
}

void	think(t_philo *philo)
{
	display_message(philo, "is thinking");
}
