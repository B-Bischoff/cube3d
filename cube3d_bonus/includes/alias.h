/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <brice@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:00:41 by bbischof          #+#    #+#             */
/*   Updated: 2022/05/29 12:14:45 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

#ifndef OS
# define OS 1
# endif

#if (OS == 1) // MAC OS
	// Terminal colors
	# define TERM_END "\x1b[0m"
	# define TERM_RED "\x1b[31m"
	# define TERM_GREEN "\x1b[32m"
	# define TERM_BLUE "\x1b[34m"
	# define TERM_ERASE "\033[2K\r"
	# define TERM_BCKG_END "\x1b[0m"
	# define TERM_BCKG_RED "\x1b[41m"
	# define TERM_BCKG_GREEN "\x1b[42m"
	# define TERM_BCKG_YELLOW "\x1b[43m"
	# define TERM_BCKG_BLUE "\x1b[44m"
	# define TERM_BCKG_MAGENTA "\x1b[45m"
	# define TERM_BCKG_CYAN "\x1b[46m"
	# define TERM_BCKG_WHITE "\x1b[47m"

	// Keycode
	# define MOUSE_UP 4
	# define MOUSE_DOWN 5
	# define MOUSE_WHELL 3
	# define LMB 1
	# define RMB 2
	# define KEY_C 8
	# define KEY_V 9
	# define KEY_B 11
	# define KEY_Q 12
	# define KEY_R 15
	# define KEY_O 31
	# define KEY_P 35
	# define KEY_TAB 48
	# define KEY_ESC 53
	# define KEY_UP 126
	# define KEY_DOWN 125
	# define KEY_LEFT 123
	# define KEY_RIGHT 124
	# define KEY_W 13
	# define KEY_E 14
	# define KEY_S 1
	# define KEY_A 0
	# define KEY_D 2
	# define KEY_1 83
	# define KEY_2 84
	# define KEY_4 86
	# define KEY_5 87
	# define KEY_7 89
	# define KEY_8 91
	# define KEY_PLUS 69
	# define KEY_MINUS 78
#endif

#if (OS == 2) // LINUX
	// Terminal colors
	# define TERM_END "\033[0m"
	# define TERM_RED "\033[31m"
	# define TERM_GREEN "\033[32m"
	# define TERM_BLUE "\033[34m"
	# define TERM_ERASE "\033[2K\r"
	# define TERM_BCKG_END "\033[0m"
	# define TERM_BCKG_RED "\033[41m"
	# define TERM_BCKG_GREEN "\033[42m"
	# define TERM_BCKG_YELLOW "\033[43m"
	# define TERM_BCKG_BLUE "\033[44m"
	# define TERM_BCKG_MAGENTA "\033[45m"
	# define TERM_BCKG_CYAN "\033[46m"
	# define TERM_BCKG_WHITE "\033[47m"

	# define LMB 1
	# define RMB 3
	# define MOUSE_UP 4
	# define MOUSE_DOWN 5
	# define KEY_C 98
	# define KEY_V 99
	# define KEY_B 118	
	# define KEY_Q 113
	# define KEY_R 114
	# define KEY_O 111
	# define KEY_P 112
	# define KEY_E 101
	# define KEY_ESC 65307 % 200
	# define KEY_UP 65364 % 200
	# define KEY_DOWN 65362 % 200
	# define KEY_LEFT 65361 % 200
	# define KEY_RIGHT 65363 % 200
	# define KEY_W 119 % 200
	# define KEY_S 115 % 200
	# define KEY_A 97 % 200
	# define KEY_D 100 % 200
	# define KEY_1 836 % 200
	# define KEY_2 49 % 200
	# define KEY_3 50 % 200
	# define KEY_4 51 % 200
	# define KEY_5 52 % 200
	# define KEY_6 53 % 200
	# define KEY_7 54 % 200
	# define KEY_8 55 % 200
	# define KEY_TAB 65289 % 200

#endif

// MLX Colors
# define WHITE 0x00FFFFFF
# define DARK_GRAY 0x00222222
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define PURPLE 0x00FF00FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF
# define PINK 0x00DD88BB
# define LIGHT_BLUE 0x00AAAAFF

#endif