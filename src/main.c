/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:30:35 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/23 21:29:48 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

int g_counter = 0;

char	*get_user_input(Data *data)
{
	char	*line;

	line = NULL;
	while (!line)
	{
		line = readline(data->prompt);
		if (!line) // NULL (empty imput) → Ctrl+D pressed (EOF)
			cleanup(data, END);
		else if (*line) // input
		{
			if (!parse_input(data, line))
			{
				free(line);
				line = NULL;
				continue ;
			}
		}
		else
		{
			free(line);
			line = NULL;
			continue ;
		}
	}
	return (line);
}

static int	init_data(Data *data)
{
	ft_memset(data, 0, sizeof(Data));
	data->prompt = ft_strdup("Input: ");
	if (!data->prompt)
		return (0);

	data->color = ft_calloc(6, sizeof(t_color));
	if (!data->color)
		return (0);
	srand(time(NULL));
	return (1);
}

int	main(int ac, char **av)
{
	Data	data;
	char	*line;
	int		attempt;

start:
	attempt = 0;
	(void)av;
	line = NULL;

	if (ac != 1)
		return (0);
	if (!init_data(&data) || !get_secret_word(&data))
		cleanup(&data, END);
	print_wordle_logo();
	while (attempt != 6)
	{
		print_game(data.color, &data, RUN);
		line = get_user_input(&data);
		if (set_colors(&data, data.color, line))
		{
			break;
		}
		free(line);
		line = NULL;
		attempt++;
	}
	if (attempt == 6)
		print_lose(&data);
	else
		print_win(&data);
	free(line);
	line = NULL;
	cleanup(&data, TRY_AGAIN);
	if (restart(&data))
		goto start;
	return (0);
}
