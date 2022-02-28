/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:12:45 by hrecolet          #+#    #+#             */
/*   Updated: 2022/02/24 11:55:20 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	display_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->var->mutex);
	if (philo->var->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->var->mutex);
		return ;
	}
	printf("%d %d %s\n", get_time() - philo->var->start, philo->id, message);
	pthread_mutex_unlock(&philo->var->mutex);
}

void	join_thread(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->nb_philo)
	{
		pthread_join(var->philos[i].id_thread, NULL);
		i++;
	}
}

void	ft_usleep(int time, t_philo *philo)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time && !ft_is_dead(philo))
		usleep(1);
}
