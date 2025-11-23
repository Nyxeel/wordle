/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:25:50 by netrunner         #+#    #+#             */
/*   Updated: 2025/11/23 03:45:10 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

void	print_invitation(void)
{
	printf("WORDLE\n");
	// printf("Total words availible 12972\n\n");
}

void	print_status(t_color *color)
{
	int j = 0;
	printf("\n");
	while (j < g_counter)
	{
		printf("\n\t");
		int i = 0;
		while (color[j].str[i])
		{
			if (color[j].state[i] == GREEN)
				printf("\e[1;92m%c\e[0m ", color[j].str[i]);
			else if (color[j].state[i] == YELLOW)
				printf("\e[1;93m%c\e[0m ", color[j].str[i]);
			else if (color[j].state[i] == GREY)
				printf("\e[1;90m%c\e[0m ", color[j].str[i]);
			i++;
		}
		printf("\n");
		j++;
	}
	for (int i = 0; i < 6 - g_counter; i++)
	{
		printf("\n\t_ _ _ _ _\n");
	}
	printf("\n");
}

void	print_lose_message(Data *data)
{
	printf("END. You loose\n");
	printf("The correct word is %s\n", data->secret_word);
	cleanup(data, TRY_AGAIN);
}

void	congrats(void)
{
	printf("Congrats! You win!\n");
}