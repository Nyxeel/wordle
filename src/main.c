/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:30:35 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/23 03:40:17 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

int g_counter = 0;


void	free_darr(Data *data)
{
	int	i;

	if (!data->wordlist)
		return ;
	i = 0;
	while (data->wordlist[i])
		free(data->wordlist[i++]);
	free(data->wordlist);
	data->wordlist = NULL;
}

void	cleanup(Data *data, int flag)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->color)
	{
		free(data->color);
		data->color = NULL;
	}
	free_darr(data);
	if (flag == END)
		exit(0);
}

ssize_t	count_dictionary_lines(Data *data)
{
	int		fd;
	int		count;
	char	*line;

	fd = open("words.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("file not found!\n");
		cleanup(data, END);
	}
	data->wordlist = calloc(12972 + 1, sizeof(char *)); // words.txt has 12972 lines!
	if (!data->wordlist)
		return (close(fd), -1);
	count = 0;
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
	return (count);
}

int	get_secret_word(Data *data)
{
	ssize_t	count;
	ssize_t	rnd_num;
	ssize_t	i;
	char	*line;

	count = count_dictionary_lines(data);
	if (count == -1)
		return (0);
	rnd_num = (rand() % count);
	if (VERBOSE)
		printf("RND NWORD IN LINE: %li\n", rnd_num);
	i = 0;
	line = NULL;
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


char	*get_user_input(Data *data)
{
	char	*line;

	line = NULL;
	while (!line)
	{
		line = readline(data->prompt);
		if (!line) // NULL (empty imput) → Ctrl+D pressed (EOF)
			cleanup(data, END);
		if (*line) // input
		{
			if (!parse_input(data, line))
			{
				free(line);
				line = NULL;
				continue ;
			}
		}
	}
	return (line);
}

int	init_data(Data *data)
{
	memset(data, 0, sizeof(Data));
	data->prompt = ft_strdup("Input: ");
	if (!data->prompt)
		return (0);

	data->color = ft_calloc(7, sizeof(t_color));
	if (!data->color)
		return (1);
	srand(time(NULL));
	return (1);
}

int	main(int ac, char **av)
{
start:
	Data	data;
	char	*line;
	int		attempt;

	
	attempt = 0;
	(void)av;
	line = NULL;
	if (ac != 1)
		return (0);
	if (!init_data(&data))
		exit(1);
	
	if (!get_secret_word(&data))
		cleanup(&data, END);
	if (VERBOSE)
		printf("SECRET WORD: %s\n", data.secret_word);
	print_invitation();
	while (attempt != 6)
	{
		print_status(data.color);
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
		print_lose_message(&data);
	else	
		congrats();
	cleanup(&data, TRY_AGAIN);
	free(line);
	line = NULL;
	if (restart(&data))
		goto start;	
	printf("Thanks for gaming!\n");

	return (0);
}
