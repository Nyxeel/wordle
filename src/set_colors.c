/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:59:37 by netrunner         #+#    #+#             */
/*   Updated: 2025/11/23 03:32:11 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

//COLOR THEM 
int	set_colors(Data *data, t_color *color, char *str)
{
	int i = 0;
	static int j = 0;

	char	*c = color[j].str;
	int		freq[128] = {0};

	for(int i = 0; i < 5; i++)
		freq[(unsigned char) data->secret_word[i]]++;
	while (str[i])
	{
		// freq[(unsigned char)c[i]] = ft_count_chars(data->secret_word, c[i]);
		if ((str[i] == data->secret_word[i]))
		{
			color[j].str[i] =  str[i];
			color[j].state[i] = GREEN;
			freq[(unsigned char)c[i]]--;
		}
		else
		{
			c[i] = str[i];
			color[j].state[i] = GREY;
		}
		i++;
	}
	color[j].str[i] = 0; // str[5] is not auto '\0' terminated, it printed garbage values
	i = 0;
	while (color[j].str[i])
	{
		if (color[j].state[i] != GREEN && freq[(unsigned char)c[i]] > 0)
		{
			color[j].state[i] = YELLOW;
			freq[(unsigned char)c[i]]--;
		}
		i++;
	}
	j +=1;
	g_counter = j;
	if (ft_strncmp(data->secret_word, str, 5) == 0)
		return (1);
	return (0);
}
