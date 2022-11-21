/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:34:08 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/11/21 17:38:38 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_check(int ac, t_data *data, ssize_t val)
{
	ssize_t	i;
	ssize_t	count;

	if (val != data->nb_philo)
		return ;
	while (1)
	{
		i = -1;
		count = 0;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->guard);
			if (ft_check_utils(ac, data, i, &count)
				|| (ac == 6 && count == data->nb_philo))
			{
				data->end++;
				pthread_mutex_unlock(&data->guard);
				return ;
			}
			pthread_mutex_unlock(&data->guard);
		}
	}
}

static void	ft_eat(t_list *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	ft_display(philo->data, philo->val, "has taken a fork");
	if (philo->data->nb_philo == 1)
	{
		usleep(philo->data->time_die * 1000);
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	ft_display(philo->data, philo->val, "has taken a fork");
	ft_display(philo->data, philo->val, "is eating");
	pthread_mutex_lock(&philo->data->guard);
	philo->last_eat = ft_time(0, 0);
	pthread_mutex_unlock(&philo->data->guard);
	ft_time(1, philo->data->time_eat);
	pthread_mutex_lock(&philo->data->guard);
	philo->count_eat++;
	pthread_mutex_unlock(&philo->data->guard);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
}

static void	*ft_routine(void *list)
{
	t_list	*philo;

	philo = (t_list *)list;
	if (philo->val % 2)
	{
		philo->right_fork = philo->val % philo->data->nb_philo;
		philo->left_fork = philo->val - 1;
		ft_display(philo->data, philo->val, "is thinking");
		ft_time(1, philo->data->time_eat);
	}
	while (1)
	{
		ft_eat(philo);
		pthread_mutex_lock(&philo->data->guard);
		if (philo->data->end)
			return (pthread_mutex_unlock(&philo->data->guard), NULL);
		pthread_mutex_unlock(&philo->data->guard);
		ft_display(philo->data, philo->val, "is sleeping");
		ft_time(1, philo->data->time_sleep);
		ft_display(philo->data, philo->val, "is thinking");
		ft_time(1, philo->data->time_think);
	}
	return (NULL);
}

static int	ft_init(int ac, char **av, t_data *data, ssize_t i)
{
	data->nb_philo = ft_atos(av[1]);
	data->time_die = ft_atos(av[2]);
	data->time_eat = ft_atos(av[3]);
	data->time_sleep = ft_atos(av[4]);
	data->time_think = ((data->time_die - (data->time_eat \
			+ data->time_sleep)) / 2);
	if (ac == 6)
		data->nb_eat = ft_atos(av[5]);
	if (!data->nb_philo || !data->time_die || !data->time_eat
		|| !data->time_sleep || (ac == 6 && !data->nb_eat))
		return (-1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	data->philo = malloc(sizeof(t_list) * data->nb_philo);
	if (!data->fork || !data->philo)
		return (ft_free(data, 0, 0), -1);
	while (++i < data->nb_philo)
	{
		data->philo[i].val = i + 1;
		data->philo[i].right_fork = i;
		data->philo[i].left_fork = (i + 1) % data->nb_philo;
		data->philo[i].count_eat = 0;
		data->philo[i].last_eat = ft_time(0, 0);
		data->philo[i].data = data;
	}
	return (data->end = 0, data->time = ft_time(0, 0), 0);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	*thr;

	if (ac < 5 || ac > 6 || !av || ft_init(ac, av, &data, -1))
		return (write(2, "Error: Wrong arguments.\n", 24), -1);
	thr = malloc(sizeof(pthread_t) * data.nb_philo);
	if (!thr)
		return (ft_free(&data, thr, 0), -1);
	data.i = data.nb_philo;
	while (--data.i >= 0)
	{
		if (pthread_mutex_init(&data.fork[data.i], NULL))
			return (ft_free(&data, thr, 1), -1);
	}
	if (pthread_mutex_init(&data.print, NULL))
		return (ft_free(&data, thr, 2), -1);
	if (pthread_mutex_init(&data.guard, NULL))
		return (ft_free(&data, thr, 3), -1);
	while (++data.i < data.nb_philo && !pthread_create(&thr[data.i], NULL \
		, &ft_routine, &data.philo[data.i]))
		;
	ft_check(ac, &data, data.i);
	while (--data.i >= 0 && !pthread_join(thr[data.i], NULL))
		;
	return (ft_free(&data, thr, 3), 0);
}
