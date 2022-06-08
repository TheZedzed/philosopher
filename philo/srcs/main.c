/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:25:28 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/18 13:12:26 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_(t_monitor *master, t_philo *philos)
{
	if (master)
		free(master->forks);
	free(master);
	free(philos);
}

static int	death_(t_monitor *master, t_philo *philo)
{
	ssize_t	time;

	time = (master->time.tv_sec * 1000 + master->time.tv_usec / 1000) - master->start;
	pthread_mutex_lock(&master->philo_lock);
	if (time - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_lock(&master->master_lock);
		printf("\033[31m%ld philo[%d] died\n\033[0m", time, philo->id + 1);
		return (1);
	}
	return (0);
}

static void	*monitor(void *item)
{
	t_monitor	*master;
	t_philo		*philo;
	int			i;

	master = (t_monitor *)item;
	while (1)
	{
		i = -1;
		while (++i < master->nb)
		{
			pthread_mutex_lock(&master->master_lock);
			if (!master->max)
				return (NULL);
			philo = &master->philo[i];
			gettimeofday(&master->time, NULL);
			pthread_mutex_unlock(&master->master_lock);
			if (death_(master, philo))
				return (NULL);
			pthread_mutex_unlock(&master->philo_lock);
		}
	}
}

int	main(int ac, char **av)
{
	static t_monitor	*master = NULL;
	static t_philo		*philos = NULL;
	pthread_t			child;
	pthread_t			daddy;
	int					i;

	i = -1;
	if (init_(&master, &philos, av, ac))
	{
		if (philos && !pthread_create(&daddy, NULL, monitor, master))
		{
			while (++i < master->nb)
			{
				if (pthread_create(&child, NULL, dinner, &master->philo[i]))
					break ;
				pthread_detach(child);
				usleep(100);
			}
			pthread_join(daddy, NULL);
		}
	}
	free_(master, philos);
	return (0);
}
