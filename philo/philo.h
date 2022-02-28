/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:20:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/02/25 11:17:18 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		id_thread;
	int				id;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	struct s_vars	*var;
	int				is_eating;
	int				last_eat;
	int				wdie;
	int				count;
}	t_philo;

typedef struct s_vars
{
	int				nb_philo;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				amount_loop;
	int				start;
	t_philo			*philos;
	pthread_mutex_t	*fork_m;
	pthread_mutex_t	mutex;
	pthread_mutex_t	dead_m;
	int				is_dead;
}	t_vars;

/*----------------------------------------------------------*/
/* Checking Function	:	check.c							*/
/*----------------------------------------------------------*/

int		check_data(t_vars *var);
int		check_args(char **av);
int		check_int(char **str);

/*----------------------------------------------------------*/
/* Utils Function		:	utils1							*/
/*							utils2.c						*/
/*----------------------------------------------------------*/

int		ft_atoi(const char *str);
void	ft_free_data(t_vars *var);
int		ft_strlen(char *str);
long	ft_atol(const char *str);
void	display_message(t_philo *philo, char *message);
int		ft_is_dead(t_philo *philo);
int		get_time(void);
void	join_thread(t_vars *var);
void	ft_usleep(int time, t_philo *philo);

/*----------------------------------------------------------*/
/* Init Function	:	init.c								*/
/*----------------------------------------------------------*/

int		init_threads(t_vars *var);
int		init_vars(t_vars *var, char **av);

/*----------------------------------------------------------*/
/* Exec Function	:	main.c								*/
/*----------------------------------------------------------*/

void	*monitor(void *philo, int i, int nb_philo_count);
void	*routine(void *philo);

/*----------------------------------------------------------*/
/* Routine Function	:	routine.c							*/
/*----------------------------------------------------------*/

void	think(t_philo *philo);
void	sleeping(t_philo *philo);
int		take_forks(t_philo *philo);
void	eat(t_philo *philo);
int		ft_is_dead(t_philo *philo);

#endif
