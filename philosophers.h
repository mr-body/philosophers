#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_program
{
    int             n_philo;
    int             t_sleep;
    int             t_dead;
    int             t_eat;
    int             n_snack;
    int             is_dead;
    unsigned long   time;
    pthread_mutex_t program_mutex;
}                   t_program;

typedef struct s_philo
{
    int             id;
    unsigned long   last_snack;
    int             eaten;
    pthread_mutex_t *fork_left;
    pthread_mutex_t *fork_right;
    pthread_mutex_t *messager;
    t_program       *program;
}                   t_philo;

unsigned long      display_time(t_philo *philo);
unsigned long      ft_timestamp(void);

void              *ft_routine(void *ptr);
int               ft_monitoring(t_philo *philos);
void              ft_messager(t_philo *philo, char *info, char *icon);

void              ft_init_philo(t_philo *philo, pthread_mutex_t *fork,
                   pthread_mutex_t *messager, t_program *program);
void              ft_init_mutex(pthread_mutex_t *messager,
                   pthread_mutex_t *fork, int n_philo);
void              ft_pthread_create(pthread_t *thread, t_philo *philo,
                   int n_philo);
void              ft_join_thread(pthread_t *thread, int n_philo);
void              ft_mutex_destroy(pthread_mutex_t *fork,
                   pthread_mutex_t *messager, int n_philo);

void              init_program_mutex(t_program *program);
void              destroy_program_mutex(t_program *program);
void              set_is_dead(t_program *program, int value);
void              set_last_snack(t_philo *philo, unsigned long int value);
int               get_is_dead(t_program *program);
int               get_n_snack(t_program *program);
int               get_n_philo(t_program *program);
int               get_t_dead(t_program *program);
int get_eaten(t_philo *philo);
void set_eaten(t_philo *philo, int value);
unsigned long     get_last_snack(t_philo *philo);

#endif
