/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:35:07 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/11/21 17:36:47 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/*--------------------------------------S_LIST-------------------------------*/

typedef struct s_list
{
	size_t			val;
	size_t			right_fork;
	size_t			left_fork;
	size_t			count_eat;
	size_t			last_eat;
	struct s_data	*data;
}	t_list;

/*--------------------------------------S_DATA-------------------------------*/

typedef struct s_data
{
	int				end;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			nb_eat;
	size_t			time;
	ssize_t			i;
	ssize_t			nb_philo;
	long double		time_think;
	pthread_mutex_t	guard;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	struct s_list	*philo;
}	t_data;

/*-----------------------------------PHILO_UTILS-----------------------------*/

size_t	ft_atos(char *str);
size_t	ft_time(int val, long double to_sleep);
int		ft_check_utils(int ac, t_data *data, ssize_t i, ssize_t *count);
void	ft_display(t_data *data, size_t val, char *str);
void	ft_free(t_data *data, pthread_t *thr, int val);

/*---------------------------------------T^T---------------------------------*/

#endif
