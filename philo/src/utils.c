/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 22:05:25 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/08/13 20:00:29 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	ft_time(struct timeval timeref)
{
	struct timeval	time;
	uint64_t		msref;
	uint64_t		ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	msref = (timeref.tv_sec * 1000) + (timeref.tv_usec / 1000);
	return (ms - msref);
}

void	ft_putmsg(t_philo *ph, char *str, char *color)
{
	pthread_mutex_lock(&ph->data->mtxmsg);
	if (ph->data->dead == -1)
	{
		printf("%s", color);
		printf("%6d\t%-1d  %s\n", (int)ft_time(ph->data->timeref), ph->id, str);
		printf("%s", NOCOL);
	}
	pthread_mutex_unlock(&ph->data->mtxmsg);
}

void	ns_usleep(t_philo *ph, int time)
{
	struct timeval	ref;

	gettimeofday(&ref, NULL);
	while (ft_time(ref) != (uint64_t)time)
	{
		if (ph->data->dead != -1)
			break ;
		usleep(50);
	}
}

void	ft_freephilos(t_philo *ph)
{
	t_philo		*tmp;
	int			i;

	i = ph->data->n_philo;
	while (i-- > 0)
	{
		tmp = ph;
		ph = ph->right;
		free(tmp);
	}
}

t_philo	*ft_createlist(t_data *data)
{
	int			i;
	t_philo		*new;
	t_philo		*ph;

	i = 0;
	ph = NULL;
	data->dead = -1;
	data->satisfied = 0;
	pthread_mutex_init(&data->mtxmsg, NULL);
	if (data->n_eat == 0)
		data->satisfied = data->n_philo;
	while (++i <= data->n_philo)
	{
		new = malloc(sizeof(t_philo));
		new->id = i;
		new->meals = 0;
		new->data = data;
		new->left = NULL;
		new->right = NULL;
		pthread_mutex_init(&new->mtxmeal, NULL);
		pthread_mutex_init(&new->mtxfork, NULL);
		ft_lstaddback(&ph, new);
	}
	return (ph);
}
