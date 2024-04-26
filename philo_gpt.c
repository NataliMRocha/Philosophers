#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 200

// Structure to hold information about each philosopher
typedef struct
{
	pthread_t thread_id;           // Thread ID
	int philosopher_id;            // Philosopher ID
	pthread_mutex_t *left_fork;    // Left fork mutex
	pthread_mutex_t *right_fork;   // Right fork mutex
	int time_to_die;               // Time to die
	int time_to_eat;               // Time to eat
	int time_to_sleep;             // Time to sleep
	int num_meals;                 // Number of meals
	struct timeval last_meal_time; // Last time the philosopher ate
}				Philosopher;

// Mutex for printing
pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

// Flag to indicate if any philosopher has died
volatile bool	philosopher_died = false;

// Function to get current timestamp in milliseconds
long long	current_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

// Function to print with timestamp
void	print_with_timestamp(int philosopher_id, char *message)
{
	long long	timestamp;
	long long	timestamp;

	if (!philosopher_died)
	{
		timestamp = current_timestamp_ms();
		pthread_mutex_lock(&print_mutex);
		printf("%lld %d %s\n", timestamp, philosopher_id, message);
		pthread_mutex_unlock(&print_mutex);
	}
	else if (philosopher_died)
	{
		timestamp = current_timestamp_ms();
		pthread_mutex_lock(&print_mutex);
		printf("%lld %d %s\n", timestamp, philosopher_id, message);
		pthread_mutex_unlock(&print_mutex);
	}
}

// Function for philosopher to eat
void	eat(Philosopher *philosopher)
{
	print_with_timestamp(philosopher->philosopher_id, "is eating");
	usleep(philosopher->time_to_eat * 1000);
	gettimeofday(&philosopher->last_meal_time, NULL);
}

// Function for philosopher to sleep
void	sleep_philosopher(Philosopher *philosopher)
{
	print_with_timestamp(philosopher->philosopher_id, "is sleeping");
	usleep(philosopher->time_to_sleep * 1000);
}

// Function for philosopher to think
void	think(Philosopher *philosopher)
{
	print_with_timestamp(philosopher->philosopher_id, "is thinking");
}

// Function for philosopher to die
void	die(Philosopher *philosopher)
{
	philosopher_died = true;
	print_with_timestamp(philosopher->philosopher_id, "is dead");
	exit(0);
}

// Philosopher thread function
void	*philosopher_thread(void *arg)
{
	Philosopher	*philosopher;
	int			meals_eaten;
		struct timeval now;
	long long	time_since_last_meal;

	philosopher = (Philosopher *)arg;
	meals_eaten = 0;
	// Set last meal time to current time
	gettimeofday(&philosopher->last_meal_time, NULL);
	while (!philosopher_died && (meals_eaten < philosopher->num_meals
			|| philosopher->num_meals == 0))
	{
		// Try to pick up left fork
		pthread_mutex_lock(philosopher->left_fork);
		print_with_timestamp(philosopher->philosopher_id, "has taken a fork");
		// Try to pick up right fork
		if (pthread_mutex_trylock(philosopher->right_fork) == 0)
		{
			print_with_timestamp(philosopher->philosopher_id,
				"has taken a fork");
			// Start eating
			eat(philosopher);
			// Release forks
			pthread_mutex_unlock(philosopher->left_fork);
			pthread_mutex_unlock(philosopher->right_fork);
			meals_eaten++;
		}
		else
		{
			// Failed to pick up right fork, release left fork and try again
			pthread_mutex_unlock(philosopher->left_fork);
			usleep(1000); // Sleep for a short time to avoid busy-waiting
		}
		// Sleep after eating
		sleep_philosopher(philosopher);
		// Check if it's time to die
		gettimeofday(&now, NULL);
		time_since_last_meal = (now.tv_sec - philosopher->last_meal_time.tv_sec)
			* 1000LL + (now.tv_usec - philosopher->last_meal_time.tv_usec)
			/ 1000;
		if (time_since_last_meal >= philosopher->time_to_die)
		{
			die(philosopher);
		}
		// Think after sleeping
		think(philosopher);
	}
	pthread_exit(NULL);
}

int	main(int argc, char *argv[])
{
	int num_meals;
	// Check for correct number of arguments
	if (argc < 5 || argc > 6)
	{
		fprintf(stderr, "Usage: %s number_of_philosophers time_to_die \
		time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
		return (1);
	}

	// Parse arguments
	int num_philosophers = atoi(argv[1]);
	int time_to_die = atoi(argv[2]);
	int time_to_eat = atoi(argv[3]);
	int time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		num_meals = atoi(argv[5]);

	// Initialize mutexes for forks
	pthread_mutex_t fork_mutexes[num_philosophers];
	for (int i = 0; i < num_philosophers; i++)
	{
		pthread_mutex_init(&fork_mutexes[i], NULL);
	}

	// Create philosopher threads
	Philosopher philosophers[num_philosophers];
	for (int i = 0; i < num_philosophers; i++)
	{
		philosophers[i].philosopher_id = i + 1;
		philosophers[i].left_fork = &fork_mutexes[i];
		philosophers[i].right_fork = &fork_mutexes[(i + 1) % num_philosophers];
		philosophers[i].time_to_die = time_to_die;
		philosophers[i].time_to_eat = time_to_eat;
		philosophers[i].time_to_sleep = time_to_sleep;
		philosophers[i].num_meals = num_meals;
		pthread_create(&philosophers[i].thread_id, NULL, philosopher_thread,
			&philosophers[i]);
	}

	// Join philosopher threads
	for (int i = 0; i < num_philosophers; i++)
	{
		pthread_join(philosophers[i].thread_id, NULL);
	}

	// Destroy mutexes for forks
	for (int i = 0; i < num_philosophers; i++)
	{
		pthread_mutex_destroy(&fork_mutexes[i]);
	}

	return (0);
}