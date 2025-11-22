/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:59:37 by netrunner         #+#    #+#             */
/*   Updated: 2025/11/22 23:27:49 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

static int	ft_count_chars(char const *set, char const c)
{
	int	i;
	int count = 0;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			count++;
		i++;
	}
	return (count);
}

//COLOR THEM 
int	set_colors(Data *data, t_color *color, char *str)
{
	int i = 0;
	static int j = 0;

	char	*c = color[j].str;
	int		freq[128] = {0};

	for(int i = 0; i < 5; i++)
		freq[(unsigned char)c[i]]++;
	while (str[i])
	{
		freq[(unsigned char)c[i]] = ft_count_chars(data->secret_word, c[i]);
		if ((str[i] == data->secret_word[i]))
		{
			c[i] = str[i];
			color[j].state[i] = GREEN;
			if (freq[(unsigned char)c[i]] < 0)
				freq[(unsigned char)c[i]]--;
		}
		else
		{
			c[i] = str[i];
			color[j].state[i] = GREY;
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		
		if (color[j].state[i] != GREEN && color->freq[(unsigned char)c[i]] < 0)
		{
			c[i] = YELLOW;
			freq[(unsigned char)c[i]]--;
		}
		i++;
	}
	i = 0;
	if (VERBOSE)
	{
		printf("\nOutput set_green\n");
		while (color->str[i])
		{
			if (color[j].state[i] == GREEN)
				printf(" \e[1;92m%c\e[0m", color->str[i]);
			if (color[j].state[i] == YELLOW)
				printf(" \e[1;93m%c\e[0m", color->str[i]);
			else
				printf(" \e[1;90m%c\e[0m", color->str[i]);
			i++;
		}
		printf("\n");
	}
	j +=1;
	return (0);
}

int	check_comparison(Data *data, t_color *color, char *input)
{
	set_colors(data, color, input);
	return (0);
}
