/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:25:50 by netrunner         #+#    #+#             */
/*   Updated: 2025/11/23 17:43:44 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

void	print_wordle_logo(void)
{
	printf("__        _____  ____  ____  _     _____ \n");
	printf("\\ \\      / / _ \\|  _ \\|  _ \\| |   | ____|\n");
	printf(" \\ \\ /\\ / / | | | |_) | | | | |   |  _|  \n");
	printf("  \\ V  V /| |_| |  _ <| |_| | |___| |___ \n");
	printf("   \\_/\\_/  \\___/|_| \\_\\____/|_____|_____|\n");
	printf("\n");
}

void	print_game(t_color *color, Data *data, int status)
{
	int j = 0;
	if (VERBOSE)
	{
		printf("\nSECRET WORD: %s\n", data->secret_word);
		printf("g_counter: %i", g_counter);
	}
	printf("\n");
	while (j < g_counter)
	{
		printf("\n\t");
		int i = 0;
		while (color[j].str[i])
		{
			if (status == LOSE && j + 1 == 6)
			{
				printf("\e[1;91m%c\e[0m ", color[j].str[i]);
				goto end;
			}
			if (color[j].state[i] == GREEN)
				printf("\e[1;92m%c\e[0m ", color[j].str[i]);
			else if (color[j].state[i] == YELLOW)
				printf("\e[1;93m%c\e[0m ", color[j].str[i]);
			else if (color[j].state[i] == GREY)
				printf("\e[1;90m%c\e[0m ", color[j].str[i]);
			end:
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

void	print_lose(Data *data)
{
	print_game(data->color, data, LOSE);
	printf("\e[1;91m		      _           _     _ \n");
	printf(" _   _  ___  _   _   | | ___  ___| |_  | |\n");
	printf("| | | |/ _ \\| | | |  | |/ _ \\/ __| __| | |\n");
	printf("| |_| | (_) | |_| |  | | (_) \\__ \\ |_  |_|\n");
	printf(" \\__, |\\___/ \\__,_|  |_|\\___/|___/\\__| (_)\n");
	printf(" |___/   \n");
	printf("\e[0m\n");
	printf("The correct word is %s", data->secret_word);
}

void	print_win(Data *data)
{
	print_game(data->color, data, WIN);
	printf("\e[1;92m                                           _ \n");
	printf(" _   _  ___  _   _  __      _____  _ __   | |\n");
	printf("| | | |/ _ \\| | | | \\ \\ /\\ / / _ \\| '_ \\  | |\n");
	printf("| |_| | (_) | |_| |  \\ V  V / (_) | | | | |_|\n");
	printf(" \\__, |\\___/ \\__,_|   \\_/\\_/ \\___/|_| |_| (_)\n");                                 
	printf(" |___/\n");
	printf("\e[0m\n");
}