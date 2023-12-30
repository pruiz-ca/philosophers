/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 21:55:58 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/08/13 19:54:31 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FORK "has taken a fork\t\U0001F962"
# define EAT "is eating\t\t\U0001F35C"
# define SLEEP "is sleeping\t\t\U0001F4A4"
# define THINK "is thinking\t\t\U0001F9E0"
# define DIED "died\t\t\t\U0001F480"

# define NOCOL "\001\e[0m\002"
# define RED "\001\e[0;31m\002"
# define GRN "\001\e[0;32m\002"
# define YEL "\001\e[0;33m\002"
# define BLU "\001\e[0;34m\002"
# define MAG "\001\e[0;35m\002"
# define CYN "\001\e[0;36m\002"
# define WHT "\001\e[0;37m\002"

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <inttypes.h>

typedef struct s_data
{
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	int					dead;
	int					satisfied;
	pthread_mutex_t		mtxmsg;
	struct timeval		timeref;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					meals;
	pthread_t			ph;
	pthread_mutex_t		mtxfork;
	pthread_mutex_t		mtxmeal;
	struct timeval		lastmeal;
	struct s_philo		*left;
	struct s_philo		*right;
	t_data				*data;
}						t_philo;

/*
** ACTIONS
*/
void		ft_fork(t_philo *ph, pthread_mutex_t *fst, pthread_mutex_t *scnd);
void		ft_eat(t_philo *philos);
void		ft_sleep(t_philo *philos);
void		*ft_start(void *tmp);
void		*ft_checkdeath(void *ph);

/*
** LIB
*/
int			ft_isdigit(char *str);
int			ft_atoi(const char *str);
void		ft_lstaddback(t_philo **lst, t_philo *new);

/*
** UTILS
*/
uint64_t	ft_time(struct timeval timeref);
void		ft_putmsg(t_philo *ph, char *str, char *color);
void		ns_usleep(t_philo *ph, int time);
void		ft_freephilos(t_philo *ph);
t_philo		*ft_createlist(t_data *data);

#endif
