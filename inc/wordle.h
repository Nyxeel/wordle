/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/23 04:48:47 by netrunner        ###   ########.fr       */
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

# define END 0
# define TRY_AGAIN 1

# define NO 'n'
# define YES 'y'

# define RUN 0
# define LOSE 1
# define WIN 2


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
	char	str[6];
	int		state[5];
	
}	t_color;

typedef struct s_data
{
	char	*prompt;
	char	*secret_word;
	char	**wordlist;
	char	*attempts[6];
	uint	number_of_tries;
	t_color	*color;

}	Data;

int		parse_input(Data *data, char *input);
int		set_colors(Data *data, t_color *color, char *input);
int 	restart(Data *data);
void	cleanup(Data *data, int flag);

//PRINT
void	print_wordle_logo(void);
void	print_status(t_color *color, Data *data, int status);
void	print_lose_message(Data *data);
void	congrats(Data *data);

// wordle.h
extern int g_counter;

#endif
