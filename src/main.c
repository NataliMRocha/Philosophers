/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoreir <namoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:46:42 by namoreir          #+#    #+#             */
/*   Updated: 2024/04/27 17:32:20 by namoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv))
		exit(EXIT_FAILURE);
	parsing(&table, argv, argc);
	init(&table);
// 	dinner_time(&table);
// 	clean(&table);
}