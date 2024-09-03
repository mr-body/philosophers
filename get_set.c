#include "philosophers.h"

void set_is_dead(t_program *program, int value)
{
    pthread_mutex_lock(&program->program_mutex);
    program->is_dead = value;
    pthread_mutex_unlock(&program->program_mutex);
}

int get_is_dead(t_program *program)
{
    int value;

    pthread_mutex_lock(&program->program_mutex);
    value = program->is_dead;
    pthread_mutex_unlock(&program->program_mutex);
    return value;
}

void set_last_snack(t_philo *philo, unsigned long int value)
{
    pthread_mutex_lock(philo->messager);
    philo->last_snack = value;
    pthread_mutex_unlock(philo->messager);
}

unsigned long get_last_snack(t_philo *philo)
{
    unsigned long value;

    pthread_mutex_lock(philo->messager);
    value = philo->last_snack;
    pthread_mutex_unlock(philo->messager);
    return value;
}

void set_eaten(t_philo *philo, int value)
{
    pthread_mutex_lock(philo->messager);
    philo->eaten = value;
    pthread_mutex_unlock(philo->messager);
}

int get_eaten(t_philo *philo)
{
    int value;

    pthread_mutex_lock(philo->messager);
    value = philo->eaten;
    pthread_mutex_unlock(philo->messager);
    return value;
}
