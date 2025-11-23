/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:21:36 by netrunner         #+#    #+#             */
/*   Updated: 2025/11/23 21:32:59 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

static bool	word_in_dictionary(char *input, Data *data)
{
	int i = 0;
	while (data->wordlist[i])
	{
		if (ft_strncmp(data->wordlist[i], input, ft_strlen(input)) == 0)
			return (true); ///Check for ft_strlen fail ??
		i++;
	}
	return (false);
}

int	parse_input(Data *data, char *input)
{
	(void) data;
	int i = 0;
	if (!input || !*input)
		return (0);
	if (ft_strlen(input) != 5)
		return (printf("\nEnter exactly 5 characters - try again\n"), 0);
	while (input[i])
	{
		if (!ft_isalpha(input[i]))
			return (printf("\nOnly letters allowed! - try again\n"), 0);
		if (!word_in_dictionary(input, data))
			return (printf("\nWord ist not in dictionary - try again\n"), 0);
		i++;
	}
	return (1);
}
