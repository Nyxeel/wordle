/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:46:00 by netrunner         #+#    #+#             */
/*   Updated: 2025/11/23 17:23:18 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wordle.h"

static void	free_darr(Data *data)
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