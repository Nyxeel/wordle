/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_secret.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:47:31 by netrunner         #+#    #+#             */
/*   Updated: 2025/11/23 17:21:45 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

static ssize_t	count_dictionary_lines(Data *data)
{
	int		fd;
	int		count;
	char	*line;

	fd = open("words.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("file not found!\n");
		return (-1);
	}
	data->wordlist = calloc(12972 + 1, sizeof(char *)); // words.txt has 12972 lines!
	if (!data->wordlist)
		return (close(fd), -1);
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		data->wordlist[count] = ft_strdup(line);
		if (!data->wordlist[count])
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
	char	*line = NULL;

	count = count_dictionary_lines(data);
	if (count == -1)
		return (0);
	rnd_num = (rand() % count);
	i = 0;
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