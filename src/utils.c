/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_oc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoreir <namoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:27:33 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/26 16:47:56 by namoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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