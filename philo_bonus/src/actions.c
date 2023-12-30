/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 11:55:00 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/08/13 19:57:10 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_fork(t_philo *ph, int time)
{
	usleep(time);
	sem_wait(ph->data->fork);
	ft_putmsg(ph, FORK, YEL, 0);
	sem_wait(ph->data->fork);
	ft_putmsg(ph, FORK, YEL, 0);
}

void	ft_eat(t_philo *ph)
{
	sem_wait(ph->data->meal);
	ft_putmsg(ph, EAT, GRN, 0);
	gettimeofday(&ph->lastmeal, NULL);
	sem_post(ph->data->meal);
	ns_usleep(ph, ph->data->t_eat);
	ph->meals++;
	sem_wait(ph->data->meal);
	if (ph->meals == ph->data->n_eat)
		ph->data->satisfied++;
	sem_post(ph->data->meal);
	sem_post(ph->data->fork);
	sem_post(ph->data->fork);
}

void	ft_sleep(t_philo *ph)
{
	ft_putmsg(ph, SLEEP, BLU, 0);
	ns_usleep(ph, ph->data->t_sleep);
	ft_putmsg(ph, THINK, MAG, 0);
}

void	*ft_start(void *tmp)
{
	t_philo		*ph;
	pthread_t	death;

	ph = (t_philo *)tmp;
	gettimeofday(&ph->lastmeal, NULL);
	pthread_create(&death, NULL, ft_checkdeath, ph);
	pthread_detach(death);
	while (ph->meals < ph->data->n_eat || ph->data->n_eat == -1)
	{
		if (!(ph->id % 2))
			ft_fork(ph, 0);
		else
			ft_fork(ph, 150);
		ft_eat(ph);
		ft_sleep(ph);
	}
	return (NULL);
}

void	*ft_checkdeath(void *tmp)
{
	t_philo		*ph;

	ph = (t_philo *)tmp;
	while (1)
	{
		usleep(100);
		if (ph->data->satisfied == ph->data->n_philo)
			break ;
		sem_wait(ph->data->meal);
		if (ft_time(ph->lastmeal) > (uint64_t)ph->data->t_die)
		{
			sem_post(ph->data->meal);
			ft_putmsg(ph, DIED, RED, 1);
			exit (0);
		}
		sem_post(ph->data->meal);
	}
	return (NULL);
}
