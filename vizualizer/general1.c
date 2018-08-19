/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noprysk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:54:39 by noprysk           #+#    #+#             */
/*   Updated: 2018/05/01 17:54:41 by noprysk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void			init_ncurses(void)
{
	initscr();
	noecho();
	curs_set(0);
	start_color();
	init_pair(C_DEFAULT, COLOR_GREY, COLOR_BLACK);
	init_pair(BOARDER, COLOR_GREY, COLOR_GREY);
	init_pair(C_PLAYER1, COLOR_CYAN, COLOR_BLACK);
	init_pair(C_PLAYER2, COLOR_RED, COLOR_BLACK);
	init_pair(C_PLAYER3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(C_PLAYER4, COLOR_BLUE, COLOR_BLACK);
	init_pair(C_PROCESS_DEFAULT, COLOR_BLACK, COLOR_WHITE);
	init_pair(C_PROCESS_P1, COLOR_BLACK, COLOR_CYAN);
	init_pair(C_PROCESS_P2, COLOR_BLACK, COLOR_RED);
	init_pair(C_PROCESS_P3, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(C_PROCESS_P4, COLOR_BLACK, COLOR_BLUE);
	init_pair(C_BRIGHT_WHITE, WHITE_COLOR, COLOR_BLACK);
	init_pair(C_DEAD_PROCESS, COLOR_BLACK, COLOR_YELLOW);
	init_pair(C_ACTIVE_BAR, COLOR_GREEN, COLOR_BLACK);
	init_pair(C_PASSIVE_BAR, COLOR_GREY, COLOR_BLACK);
	mousemask(ALL_MOUSE_EVENTS, NULL);
}

void			print_boarder_of_window(WINDOW *window)
{
	wattron(window, COLOR_PAIR(BOARDER));
	wborder(window, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(window, COLOR_PAIR(BOARDER));
}

void			print_boarder(WINDOW **windows)
{
	int			i;

	i = 0;
	while (i < NB_OF_WINDOWS)
		print_boarder_of_window(windows[i++]);
}

void			open_windows(WINDOW **windows)
{
	windows[MAIN_FIELD] = newwin(ROWS + 2, CHARS_IN_LINE + 2, 0, 0);
	windows[MAIN_INFO] = newwin((ROWS + 8) / 2,
		NB_OF_COLUMNS_OF_MAIN_INFO, 0, CHARS_IN_LINE + 2);
	windows[PROCESS_INFO] = newwin((ROWS - 1) / 4,
		NB_OF_COLUMNS_OF_MAIN_INFO, (ROWS + 6) / 2, CHARS_IN_LINE + 2);
	windows[HOTKEYS_INFO] = newwin((ROWS + 7) / 4,
		NB_OF_COLUMNS_OF_MAIN_INFO, (28 + ROWS + 6) / 2, CHARS_IN_LINE + 2);
}

void			close_windows(WINDOW **windows)
{
	delwin(windows[MAIN_FIELD]);
	delwin(windows[MAIN_INFO]);
	delwin(windows[PROCESS_INFO]);
	delwin(windows[HOTKEYS_INFO]);
	endwin();
}
