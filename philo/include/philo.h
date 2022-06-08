/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:28:14 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/15 20:28:15 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

enum {SLEEP, THINK, EAT, FORK
};

typedef struct timeval		t_val;
typedef struct s_philo		t_philo;
typedef struct s_monitor	t_monitor;
typedef pthread_mutex_t		t_mutex;

struct	s_philo {
	int			id;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	ssize_t		last_meal;
	t_monitor	*master;
};

struct	s_monitor {
	int		nb;
	int		max;
	size_t	start;
	t_val	time;
	t_philo	*philo;
	t_mutex	master_lock;
	t_mutex	philo_lock;
	t_mutex	*forks;
};

void	*dinner(void *item);
int		init_(t_monitor **master, t_philo **philos, char **av, int ac);
#endif
