/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/22 22:38:43 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORDLE_H
# define WORDLE_H
# define _DEFAULT_SOURCE

# ifndef VERBOSE
#  define VERBOSE 0
# endif

# define GREEN 0
# define YELLOW 1
# define GREY 2

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_color
{
	char	str[5];
	int		state[5];
	int		*freq;
}	t_color;

typedef struct s_data
{
	char	*prompt;
	char	*secret_word;
	char	**wordlist;
	char	*attempts[6];
	uint	number_of_tries;

}	Data;

int		parse_input(Data *data, char *input);
int		check_comparison(Data *data, t_color *color, char *input);


#endif
