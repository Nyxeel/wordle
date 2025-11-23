/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:13:02 by netrunner         #+#    #+#             */
/*   Updated: 2025/11/23 04:07:14 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

int restart(Data *data)
{
	char *line = NULL;
	while (1)
	{
		line = readline("Try again? y/n ");
		if (!line) // NULL (empty imput) → Ctrl+D pressed (EOF)
			cleanup(data, END);
		if (*line)
		{
			if (ft_strlen(line) != 1)
			{
				printf("Enter max. 1 letter\n");
				continue;
			}
			if (*line == YES)
			{
				g_counter = 0;
				return(free(line), TRY_AGAIN);
			}
			else if (*line == NO)
				return(free(line), END);
			else
				printf("Just choose between 'y' and 'n'!\n");
			free(line);
		}
	}
}