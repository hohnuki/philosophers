#include "../include/philo.h"

static void	philo_eat_fin(t_philo *philo)
{
	philo->has_fork_left = 0;
	philo->has_fork_right = 0;
	philo->eat_count++;
}

static int	philo_eat_core(t_philo *philo)
{
	if (philo->has_fork_right == 1 && philo->has_fork_left == 1)
	{
		if (print_action(philo, "is eating") == 1)
			return (1);
		philo->last_eat_time = get_time_zero_start(philo);
		if (time_keeper(philo, philo->data->time_to_eat) == 1)
			return (1);
		if (philo->philo_number != philo->data->number_of_philo)
		{
			pthread_mutex_unlock(&(philo->data->forks_mutex[philo->philo_number - 1]));
			pthread_mutex_unlock(&(philo->data->forks_mutex[philo->philo_number]));
		}
		else
		{
			pthread_mutex_unlock(&(philo->data->forks_mutex[philo->philo_number - 1]));
			pthread_mutex_unlock(&(philo->data->forks_mutex[0]));
		}
		philo_eat_fin(philo);
	}
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (philo->data->is_finished == 1)
		return (1);
	else
		pthread_mutex_unlock(&philo->data->shared_mutex);
	if (philo_eat_core(philo) == 1)
		return (1);
	return (0);
}
