/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:28:14 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/15 20:28:15 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

enum {SLEEP, THINK, EAT, FORK
};

typedef struct timeval		t_val;
typedef struct s_philo		t_philo;
typedef struct s_monitor	t_monitor;

struct	s_philo {
	int		id;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	ssize_t	last_meal;
};

struct	s_monitor {
	int		nb;
	int		max;
	size_t	start;
	t_val	time;
	sem_t	*end;
	sem_t	*eat;
	sem_t	*forks;
	sem_t	*master_lock;
	t_philo	*philo;
};

void	dinner(t_monitor *master);
int		init_(t_monitor **master, t_philo **philos, char **av, int ac);
#endif
