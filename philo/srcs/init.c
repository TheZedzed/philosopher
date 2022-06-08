/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:28:35 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/15 20:28:36 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	my_len(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

static int	my_atoi(char *str)
{
	int	num;

	num = 0;
	if (my_len(str) <= 10)
	{
		while (*str)
		{
			if (!(*str >= '0' && *str <= '9'))
				break ;
			num = num * 10 + (*str - 48);
			++str;
		}
	}
	if (!*str && num >= 0)
		return (num);
	return (-1);
}

static int	initp_(t_monitor **master, t_philo **philos, char **av)
{
	ssize_t	time;
	int		i;

	i = -1;
	(*philos) = malloc(sizeof(t_philo) * (*master)->nb);
	if (*philos)
	{
		(*master)->philo = *philos;
		time = ((*master)->time.tv_sec * 1000 + (*master)->time.tv_usec / 1000) - (*master)->start;
		while (++i < (*master)->nb)
		{
			(*philos)[i].id = i;
			(*philos)[i].master = *master;
			(*philos)[i].last_meal = time;
			(*philos)[i].time_to_die = my_atoi(av[2]);
			(*philos)[i].time_to_eat = my_atoi(av[3]);
			(*philos)[i].time_to_sleep = my_atoi(av[4]);
		}
	}
	return (1);
}

static int	initm_(t_monitor **master, t_philo **philos, char **av, int ac)
{
	int	i;

	i = -1;
	(*master) = malloc(sizeof(t_monitor));
	if (*master)
	{
		(*master)->max = -1;
		(*master)->nb = my_atoi(av[1]);
		if (ac == 6)
			(*master)->max = my_atoi(av[5]) * (*master)->nb;
		(*master)->forks = malloc(sizeof(t_mutex) * (*master)->nb);
		if ((*master)->forks)
		{
			gettimeofday(&(*master)->time, NULL);
			pthread_mutex_init(&(*master)->philo_lock, NULL);
			(*master)->start = (*master)->time.tv_sec * 1000 + (*master)->time.tv_usec / 1000;
			pthread_mutex_init(&(*master)->master_lock, NULL);
			while (++i < (*master)->nb)
				pthread_mutex_init(&(*master)->forks[i], NULL);
			return (initp_(master, philos, av));
		}
	}
	return (0);
}

int	init_(t_monitor **master, t_philo **philos, char **av, int ac)
{
	if (ac == 5 || ac == 6)
	{
		if (my_atoi(av[1]) <= 0 && printf("wrong nb of philo\n"))
			return (0);
		if (my_atoi(av[2]) < 0 && printf("wrong time to die\n"))
			return (0);
		if (my_atoi(av[3]) < 0 && printf("wrong time to eat\n"))
			return (0);
		if (my_atoi(av[4]) < 0 && printf("wrong time to sleep\n"))
			return (0);
		if (ac == 6 && my_atoi(av[5]) <= 0 && printf("wrong max eat\n"))
			return (0);
	}
	else
		return (0);
	return (initm_(master, philos, av, ac));
}
