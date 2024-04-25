/* pthread_t *thread: É um ponteiro para uma variável onde o ID da thread criada será armazenado.
const pthread_attr_t *attr: É um ponteiro para uma estrutura de atributos da thread. Você pode passar NULL para usar os atributos padrão.
void	*(*start_routine) (void *): É um ponteiro para a função que será executada pela nova thread.
void *arg: É um ponteiro para os argumentos que serão passados para a função start_routine.
int	pthread_create(pthread_t *thread, const pthread_attr_t *attr,
			void *(*start_routine) (void *), void *arg);
 */

#include "../philosophers.h"

void	*thread_function(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	printf("criei a thread philo n:%d\n", data->philos);
	return (NULL);
}

int	check_args(int argc, char **argv)
{
	long long int	arg;
	int				i;

	i = 1;
	if (argc < 5)
		return (printf("tem pouco argumento"));
	if (argc > 6)
		return (printf("tem argumento demais"));
	while (argv[i])
	{
		if (argv[i][0] == '-')
			return (printf("não pode ser número negativo"));
		arg = ft_atol(argv[i]);
		if (arg > INT_MAX)
			return (printf("preciso de um arg menor ou igual ao intmax"));
		i++;
	}
	return (0);
}

// t_data* save_adress(t_data *infos)
// {
// 	t_data save;

// 	if (infos)
// 		save = *infos;
// 	return(&save);
// }

void	init(t_data *infos, char **argv, int argc)
{
	infos->philos = ft_atoi(argv[1]);
	infos->time_to_die = ft_atoi(argv[2]);
	infos->time_to_eat = ft_atoi(argv[3]);
	infos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		infos->must_eat = ft_atoi(argv[5]);
	// save_adress(infos);
}

long	currentMillis(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

int	main(int argc, char *argv[])
{
	t_data			infos;
	int				i;
	struct timeval	t1;
	struct timeval	t2;
	long			elapsedTime;

	if (check_args(argc, argv))
		return (1);
	init(&infos, argv, argc);
	i = infos.philos;
	while (i > 0)
	{
		pthread_create(&infos.tid, NULL, thread_function, &infos);
		perror("pthread_create");
		i--;
	}
	gettimeofday(&t1, NULL);
	pthread_join(infos.tid, NULL);
	gettimeofday(&t2, NULL);
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec)
		/ 1000;
	printf("Tempo decorrido: %ld ms.\n", elapsedTime);
	
	return (0);
}
