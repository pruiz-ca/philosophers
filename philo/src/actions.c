/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 11:55:00 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/08/13 20:00:44 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fork(t_philo *ph, pthread_mutex_t *fst, pthread_mutex_t *scnd)
{
	pthread_mutex_lock(fst);
	ft_putmsg(ph, FORK, YEL);
	pthread_mutex_lock(scnd);
	ft_putmsg(ph, FORK, YEL);
}

void	ft_eat(t_philo *ph)
{
	ft_putmsg(ph, EAT, GRN);
	pthread_mutex_lock(&ph->mtxmeal);
	gettimeofday(&ph->lastmeal, NULL);
	pthread_mutex_unlock(&ph->mtxmeal);
	ns_usleep(ph, ph->data->t_eat);
	ph->meals++;
	if (ph->meals == ph->data->n_eat)
	{
		pthread_mutex_lock(&ph->mtxmeal);
		ph->data->satisfied++;
		pthread_mutex_unlock(&ph->mtxmeal);
	}
	pthread_mutex_unlock(&ph->mtxfork);
	pthread_mutex_unlock(&ph->right->mtxfork);
}

void	ft_sleep(t_philo *ph)
{
	ft_putmsg(ph, SLEEP, BLU);
	ns_usleep(ph, ph->data->t_sleep);
	ft_putmsg(ph, THINK, MAG);
}

void	*ft_start(void *tmp)
{
	t_philo	*ph;

	ph = (t_philo *)tmp;
	gettimeofday(&ph->lastmeal, NULL);
	while (ph->data->dead == -1 && ph->data->satisfied != ph->data->n_philo)
	{
		if (!(ph->id % 2))
			ft_fork(ph, &ph->mtxfork, &ph->right->mtxfork);
		else
			ft_fork(ph, &ph->right->mtxfork, &ph->mtxfork);
		ft_eat(ph);
		ft_sleep(ph);
	}
	return (NULL);
}

void	*ft_checkdeath(void *ph)
{
	t_philo		*tmp;

	tmp = (t_philo *)ph;
	while (tmp->right)
	{
		usleep(100);
		if (tmp->data->satisfied == tmp->data->n_philo)
			break ;
		pthread_mutex_lock(&tmp->mtxmeal);
		if (ft_time(tmp->lastmeal) > (uint64_t)tmp->data->t_die)
		{
			ft_putmsg(tmp, DIED, RED);
			tmp->data->dead = tmp->id;
			pthread_mutex_unlock(&tmp->mtxmeal);
			pthread_mutex_unlock(&tmp->mtxfork);
			pthread_mutex_unlock(&tmp->right->mtxfork);
			break ;
		}
		pthread_mutex_unlock(&tmp->mtxmeal);
		tmp = tmp->right;
	}
	return (NULL);
}
