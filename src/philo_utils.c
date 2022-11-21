/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:30:47 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/11/21 17:37:59 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_atos(char *str)
{
	long double	nb;
	size_t		res;
	int			count;
	int			i;

	nb = 0;
	res = 0;
	count = 0;
	i = 0;
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		res = res * 10 + (str[i] - '0');
		count++;
		i++;
	}
	if ((str && str[i]) || res != nb || count > 19)
		return (0);
	return (res);
}

size_t	ft_time(int val, long double to_sleep)
{
	struct timeval	time;

	if (!val)
	{
		gettimeofday(&time, NULL);
		return ((size_t)time.tv_sec * 1000 + time.tv_usec / 1000);
	}
	else if (to_sleep > 0)
		return (usleep(to_sleep * 1000), 0);
	return (0);
}

int	ft_check_utils(int ac, t_data *data, ssize_t i, ssize_t *count)
{
	pthread_mutex_lock(&data->print);
	if (ac == 6 && data->philo[i].count_eat >= data->nb_eat)
		*count += 1;
	if (ft_time(0, 0) - data->philo[i].last_eat > data->time_die)
	{
		printf("%ld ", ft_time(0, 0) - data->time);
		printf("%ld died\n", data->philo[i].val);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	pthread_mutex_unlock(&data->print);
	return (0);
}

void	ft_display(t_data *data, size_t val, char *str)
{
	pthread_mutex_lock(&data->guard);
	pthread_mutex_lock(&data->print);
	if (data->end)
	{
		pthread_mutex_unlock(&data->guard);
		pthread_mutex_unlock(&data->print);
		return ;
	}
	pthread_mutex_unlock(&data->guard);
	printf("%ld ", ft_time(0, 0) - data->time);
	printf("%ld ", val);
	printf("%s\n", str);
	pthread_mutex_unlock(&data->print);
}

void	ft_free(t_data *data, pthread_t *thr, int val)
{
	ssize_t	i;

	if (val)
	{
		i = -1;
		while (++i < data->nb_philo)
			pthread_mutex_destroy(&data->fork[i]);
		if (val && val > 1)
			pthread_mutex_destroy(&data->print);
		if (val && val > 2)
			pthread_mutex_destroy(&data->guard);
	}
	free(thr);
	free(data->fork);
	free(data->philo);
}
