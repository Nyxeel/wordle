/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:30:35 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/22 16:05:04 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

void	free_darr(Data *data)
{
	if (!data->wordlist)
		return ;
	int i = 0;
	while (data->wordlist[i])
		free(data->wordlist[i++]);
	free(data->wordlist);
	data->wordlist = NULL;
}

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
	free_darr(data);
	exit(0);
}


ssize_t	count_dictionary_lines(Data *data)
{
	int fd = open("words.txt", O_RDONLY);
	if (fd == -1)
		return (printf("file not found!\n"), cleanup(data), 1);
	data->wordlist = calloc(12972 + 1, sizeof(char *));
	if (!data->wordlist)
		return (close(fd), -1);
	int count = 0;
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		data->wordlist[count] = ft_strdup(line);
		if (!data->wordlist)
			return (free(line), close(fd), -1);
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
	ssize_t count;


	count = count_dictionary_lines(data);
	if (count == -1)
		return (0);
	ssize_t rnd_num  = (rand() % count);
	if (VERBOSE)
		printf("RND NUMBER: %li\n", rnd_num);
	ssize_t i = 0;
	char *line = NULL;
	while (data->wordlist[i] != NULL)
	{
		if (i == rnd_num)
		{
			data->secret_word = data->wordlist[i];
			return (1);
		}
		free(line);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	Data	data;
	(void) 	av;
	char	*line = NULL;

	if (ac != 1)
		return (0);
	memset(&data, 0, sizeof(Data));
	data.prompt = ft_strdup("Your turn: ");
	if (!data.prompt)
		return (1);
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
			if (!parse_input(&data, line))
			{
				free(line);
				continue;
			}
			printf("\nInput: %s\n", line);		
		}
		free(line);
	}
	cleanup(&data);
	return (0);
}
