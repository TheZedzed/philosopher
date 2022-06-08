/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:28:42 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/15 20:28:44 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	msg_(t_monitor *master, t_philo *philo, int type)
{
	size_t	time;

	pthread_mutex_lock(&master->master_lock);
	time = (master->time.tv_sec * 1000 + master->time.tv_usec / 1000) - master->start;
	if (type == EAT)
	{
		--master->max;
		pthread_mutex_lock(&master->philo_lock);
		philo->last_meal = time;
		pthread_mutex_unlock(&master->philo_lock);
		printf("\033[33m%ld philo[%d] is eating\n", time, philo->id + 1);
	}
	else if (type == THINK)
		printf("\033[95m%ld philo[%d] is thinking\n", time, philo->id + 1);
	else if (type == SLEEP)
		printf("\033[32m%ld philo[%d] is sleeping\n", time, philo->id + 1);
	else if (type == FORK)
		printf("\033[34m%ld philo[%d] has taken a fork\n", time, philo->id + 1);
	pthread_mutex_unlock(&master->master_lock);
}

void	*dinner(void *item)
{
	t_monitor	*master;
	t_philo		*philo;

	philo = (t_philo *)item;
	master = philo->master;
	while (1)
	{
		pthread_mutex_lock(&master->forks[philo->id]);
		msg_(master, philo, FORK);
		pthread_mutex_lock(&master->forks[(philo->id + 1) % master->nb]);
		msg_(master, philo, FORK);
		msg_(master, philo, EAT);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&master->forks[philo->id]);
		pthread_mutex_unlock(&master->forks[(philo->id + 1) % master->nb]);
		msg_(master, philo, SLEEP);
		usleep(philo->time_to_sleep * 1000);
		msg_(master, philo, THINK);
	}
	return (NULL);
}
