/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 20:15:32 by pruiz-ca          #+#    #+#             */
/*   Updated: 2021/08/13 20:00:39 by pruiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	num;
	int		i;

	sign = 1;
	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num * sign >= 2147483647)
			return (2147483647);
		else if (num * sign <= -2147483648)
			return (-2147483648);
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (sign * num);
}

void	ft_lstaddback(t_philo **lst, t_philo *new)
{
	t_philo	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->right = new;
		(*lst)->left = new;
	}
	else
	{
		while (tmp->right && tmp->right != *lst)
			tmp = tmp->right;
		if (tmp)
		{
			tmp->right = new;
			new->left = tmp;
			new->right = *lst;
			(*lst)->left = new;
		}
	}
}
