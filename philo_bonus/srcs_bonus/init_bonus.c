/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:28:35 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/15 20:28:36 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static int	initp_(t_monitor *master, t_philo **philos, char **av)
{
	int	i;

	i = -1;
	*philos = malloc(sizeof(t_philo) * master->nb);
	if (*philos)
	{
		while (++i < master->nb)
		{
			(*philos)[i].id = i + 1;
			(*philos)[i].last_meal = 0;
			(*philos)[i].time_to_die = my_atoi(av[2]);
			(*philos)[i].time_to_eat = my_atoi(av[3]);
			(*philos)[i].time_to_sleep = my_atoi(av[4]);
		}
	}
	return (1);
}

static int	initm_(t_monitor **master, t_philo **philos, char **av, int ac)
{
	t_monitor	*el;

	*master = malloc(sizeof(t_monitor));
	if (*master)
	{
		el = (*master);
		el->max = -1;
		sem_unlink("sem eat");
		sem_unlink("sem fork");
		sem_unlink("sem philo");
		sem_unlink("sem master");
		el->nb = my_atoi(av[1]);
		if (ac == 6)
			el->max = my_atoi(av[5]);
		el->end = sem_open("sem end", O_CREAT, 0644, 1);
		el->eat = sem_open("sem eat", O_CREAT, 0644, 0);
		el->forks = sem_open("sem fork", O_CREAT, 0644, el->nb);
		el->master_lock = sem_open("sem master", O_CREAT, 0644, 1);
		return (initp_(*master, philos, av));
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
