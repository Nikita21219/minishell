/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:31:50 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/15 12:35:35 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define TERM_BLACK			"\033[1;90m"
# define TERM_RED			"\033[1;91m"
# define TERM_GREEN			"\033[1;92m"
# define TERM_YELLOW		"\033[1;93m"
# define TERM_BLUE			"\033[1;94m"
# define TERM_PURPLE		"\033[1;95m"
# define TERM_CYAN			"\033[1;96m"
# define TERM_WHITE			"\033[1;97m"
# define TERM_RESET			"\033[0m"

# define READLINE_BLACK		"\001\033[1;90m\002"
# define READLINE_RED		"\001\033[1;91m\002"
# define READLINE_GREEN		"\001\033[1;92m\002"
# define READLINE_YELLOW	"\001\033[1;93m\002"
# define READLINE_BLUE		"\001\033[1;94m\002"
# define READLINE_PURPLE	"\001\033[1;95m\002"
# define READLINE_CYAN		"\001\033[1;96m\002"
# define READLINE_WHITE		"\001\033[1;97m\002"
# define READLINE_RESET		"\001\033[0m\002"

# define OK					TERM_GREEN
# define WARNING			TERM_YELLOW
# define ERROR				TERM_RED
# define RESET				TERM_RESET

#endif