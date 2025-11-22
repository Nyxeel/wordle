/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:30:35 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/22 17:46:46 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

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
	int		fd;
	int		count;
	char	*line;

	fd = open("words.txt", O_RDONLY);
	if (fd == -1)
		return (printf("file not found!\n"), cleanup(data), 1);
	data->wordlist = calloc(12972 + 1, sizeof(char *));
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
	if (VERBOSE)
		printf("LINES IN FILE: %i\n", count);
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
		printf("RND NUMBER: %li\n", rnd_num);
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

void	print_invitation(void)
{
	printf("WORDLE\n");
}

void	congratulation(void)
{
	printf("Congrats! You win!\n");
}

void	print_status(Data *data)
{
	(void)data;
	printf("STATUS\n");
}

char	*get_user_input(Data *data)
{
	char	*line;

	line = NULL;
	while (!line)
	{
		line = readline(data->prompt);
		if (!line) // NULL (empty imput) → Ctrl+D pressed (EOF)
			cleanup(data);
		if (*line) // input
		{
			if (!parse_input(data, line))
			{
				free(line);
				line = NULL;
				continue ;
			}
			printf("\nInput: %s\n", line);
		}
	}
	return (line);
}

int	check_comparision(void)
{
	return (0);
}

void	print_sad_message(Data data)
{
	printf("END. You loose\n");
	printf("The correct word is %s\n", data.secret_word);
}

int	main(int ac, char **av)
{
	Data	data;
	char	*line;
	int		won;
	int		attempt;

	won = 0;
	attempt = 0;
	(void)av;
	line = NULL;
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
	print_invitation();
	while (!won && attempt < 6)
	{
		print_status(&data);
		line = get_user_input(&data);
		won = check_comparision();
		attempt++;
		free(line);
	}
	if (won)
	{
		congratulation();
	}
	else
		print_sad_message(data);
	cleanup(&data);
	return (0);
}
