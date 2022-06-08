/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:25:28 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/02 20:25:36 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat_count(t_monitor *master)
{
	int	total;
	int	i;

	i = 0;
	total = master->max * master->nb;
	while (i < total)
	{
		sem_wait(master->eat);
		++i;
	}
	sem_post(master->end);
}

static void	kill_fork(t_monitor *master, int *childs, int pid)
{
	int	status;
	int	i;

	i = -1;
	if (pid > 0)
	{
		kill(pid, SIGKILL);
		waitpid(pid, &status, 0);
	}
	while (++i < master->nb)
	{
		kill(childs[i], SIGKILL);
		waitpid(childs[i], &status, 0);
	}
}

static void	do_fork(t_monitor *master, t_philo *philos, int *childs)
{
	int	pid;
	int	i;

	i = -1;
	if (master->max > 0)
	{
		pid = fork();
		if (pid == 0)
			eat_count(master);
	}
	gettimeofday(&master->time, NULL);
	master->start = (master->time.tv_sec * 1000 + master->time.tv_usec / 1000);
	while (++i < master->nb)
	{
		master->philo = &philos[i];
		childs[i] = fork();
		if (childs[i] == 0)
			dinner(master);
		usleep(50);
	}
	sem_wait(master->end);
	if (master->max > 0)
		kill_fork(master, childs, pid);
	else
		kill_fork(master, childs, -1);
}

int	main(int ac, char **av)
{
	t_monitor	*master;
	t_philo		*philos;
	int			*childs;

	philos = NULL;
	master = NULL;
	if (init_(&master, &philos, av, ac))
	{
		childs = malloc(sizeof(int) * master->nb);
		if (philos && childs)
			do_fork(master, philos, childs);
		sem_close(master->eat);
		sem_close(master->end);
		sem_close(master->forks);
		sem_close(master->master_lock);
		free(childs);
		free(master);
		free(philos);
	}
	return (0);
}
