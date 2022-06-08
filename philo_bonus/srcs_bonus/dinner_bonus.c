/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:28:42 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/15 20:28:44 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	msg_(t_monitor *master, int type)
{
	t_philo	*philo;
	size_t	time;

	philo = master->philo;
	sem_wait(master->master_lock);
	time = (master->time.tv_sec * 1000 + master->time.tv_usec / 1000) - master->start;
	if (type == EAT)
	{
		sem_post(master->eat);
		philo->last_meal = time;
		printf("\033[33m%ld philo[%d] is eating\n", time, philo->id);
	}
	else if (type == THINK)
		printf("\033[95m%ld philo[%d] is thinking\n", time, philo->id);
	else if (type == SLEEP)
		printf("\033[32m%ld philo[%d] is sleeping\n", time, philo->id);
	else if (type == FORK)
		printf("\033[34m%ld philo[%d] has taken a fork\n", time, philo->id);
	sem_post(master->master_lock);
}

static void	*monitor(void *item)
{
	t_monitor	*master;
	t_philo		*philo;
	ssize_t		time;

	master = (t_monitor *)item;
	philo = master->philo;
	while (1)
	{
		gettimeofday(&master->time, NULL);
		time = (master->time.tv_sec * 1000 + master->time.tv_usec / 1000) - master->start;
		if (time - philo->last_meal > philo->time_to_die)
		{
			sem_wait(master->master_lock);
			printf("\033[31m%ld philo[%d] died\n\033[0m", time, philo->id);
			sem_post(master->end);
		}
	}
	return (NULL);
}

void	dinner(t_monitor *master)
{
	t_philo		*philo;
	pthread_t	daddy;

	philo = master->philo;
	if (pthread_create(&daddy, NULL, monitor, master))
		return ;
	pthread_detach(daddy);
	while (1)
	{
		sem_wait(master->forks);
		msg_(master, FORK);
		sem_wait(master->forks);
		msg_(master, FORK);
		msg_(master, EAT);
		usleep(philo->time_to_eat * 1000);
		sem_post(master->forks);
		sem_post(master->forks);
		msg_(master, SLEEP);
		usleep(philo->time_to_sleep * 1000);
		msg_(master, THINK);
	}
}
