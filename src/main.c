/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:30:35 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/22 02:59:33 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wordle.h"

void	cleanup(Data *data)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->secret_word)
	{
		free(data->secret_word);
		data->secret_word = NULL;
	}
	exit(0);
}


size_t	count_dictionary_lines(Data *data)
{
	int count = 0;
	int fd = open(data->argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("file not found!\n"), cleanup(data), 1);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		count++;
	}
	if (fd >= 0)
		close(fd);
	if (VERBOSE)
		printf("LINES IN FILE: %i\n", count);
	return (count);
}



int	get_secret_word(Data *data)
{
	size_t count;


	count = count_dictionary_lines(data);
	size_t rnd_num  = (rand() % count);
	if (VERBOSE)
		printf("RND NUMBER: %li\n", rnd_num);
	size_t i = 0;
	int fd = open(data->argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("file not found!\n"), 0);
	char *line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (i == rnd_num)
		{
			data->secret_word = line;
			return (close(fd), 1);
		}
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

int	main(int ac, char **av)
{
	char	*line;
	Data	data;

	if (ac != 2)
		return (0);
	memset(&data, 0, sizeof(Data));
	data.prompt = ft_strdup("Your turn: ");
	data.argv = av;
	srand(time(NULL));
	if (!get_secret_word(&data))
		cleanup(&data);
	if (VERBOSE)
		printf("SECRET WORD: %s", data.secret_word);
	while (1)
	{
		line = readline(data.prompt);
		if (!line) // NULL (empty imput) → Ctrl+D pressed (EOF)
			return (cleanup(&data), 0);
		if (*line) // input
		{
			printf("\nInput: %s\n", line); ///
		}
		free(line);
	}
	cleanup(&data);
	return (0);
}
