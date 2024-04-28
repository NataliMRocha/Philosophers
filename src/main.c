/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:46:42 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/28 17:57:01 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv))
		exit(EXIT_FAILURE);
	parsing(&table, argv);
	init_table(&table);
	dinner_start(&table);
	clean(&table);
}
