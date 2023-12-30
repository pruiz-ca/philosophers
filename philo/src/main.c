/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 21:58:38 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/08/13 20:00:34 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse(char **argv, t_data *data)
{
	data->n_philo = ft_atoi(argv[1]);
	if (data->n_philo < 1 || !ft_isdigit(argv[1]))
		return (0);
	data->t_die = ft_atoi(argv[2]);
	if (data->t_die < 0 || !ft_isdigit(argv[2]))
		return (0);
	data->t_eat = ft_atoi(argv[3]);
	if (data->t_eat < 0 || !ft_isdigit(argv[3]))
		return (0);
	data->t_sleep = ft_atoi(argv[4]);
	if (data->t_sleep < 0 || !ft_isdigit(argv[4]))
		return (0);
	if (argv[5])
	{
		data->n_eat = ft_atoi(argv[5]);
		if (data->n_eat < 0 || !ft_isdigit(argv[5]))
			return (0);
	}
	else
		data->n_eat = -1;
	return (1);
}

void	ft_philosophers(t_philo *ph)
{
	t_philo		*tmp;
	pthread_t	god;
	int			i;

	tmp = ph;
	i = -1;
	gettimeofday(&ph->data->timeref, NULL);
	while (++i < ph->data->n_philo)
	{
		pthread_create(&tmp->ph, NULL, ft_start, (void *)tmp);
		tmp = tmp->right;
	}
	pthread_create(&god, NULL, ft_checkdeath, (void *)tmp);
	i = -1;
	while (++i < ph->data->n_philo)
	{
		pthread_join(tmp->ph, NULL);
		pthread_mutex_destroy(&tmp->mtxfork);
		tmp = tmp->right;
	}
	pthread_mutex_destroy(&tmp->mtxmeal);
	pthread_mutex_destroy(&tmp->data->mtxmsg);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*ph;

	if (argc != 5 && argc != 6)
		return (printf("Error: bad arguments\n"));
	if (!ft_parse(argv, &data))
		return (printf("Error: bad arguments\n"));
	ph = ft_createlist(&data);
	ft_philosophers(ph);
	ft_freephilos(ph);
	return (0);
}
