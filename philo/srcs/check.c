/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:07:48 by hrecolet          #+#    #+#             */
/*   Updated: 2022/02/23 12:59:33 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_data(t_vars *var)
{
	if (var->nb_philo > 200 || var->t_die < 60 || var->t_eat < 60
		|| var->t_sleep < 60)
	{
		write(1, "No more than 200 philosophers\n", 30);
		return (1);
	}
	return (0);
}

int	check_int(char **av)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (av[i])
	{
		if (ft_strlen(av[i]) > 12)
		{
			write(1, "Number too large\n", 17);
			return (1);
		}
		nb = ft_atol(av[i]);
		if (nb < -2147483648 || nb > 2147483647)
		{
			write(1, "Number too large\n", 17);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				write (1, "Only numeric and positive parameters\n", 39);
				return (1);
			}
			j++;
		}
		i++;
	}
	if (check_int(av))
		return (1);
	return (0);
}
