/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotkeys_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noprysk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:49:10 by noprysk           #+#    #+#             */
/*   Updated: 2018/04/28 17:49:11 by noprysk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void					print_hotkeys_info(WINDOW *hotkeys_info)
{
	int					i;
	int					j;
	static const char	*keys[NB_OF_KEYS] = {"\'space\'", "\'q\'", "\'w\'",
		"\'e\'", "\'r\'", "\'escape\'",
		"\'mouse click\'", "\'h\'", "\'z\'", "\'x\'"};
	static const char	*values[NB_OF_KEYS] = {"- pause/play", "- skip 1 cycle",
		"- skip 10 cycles",
		"- skip 100 cycles", "- skip 500 cycles", "- exit", "- print info "
		"on proc", "- repeat", "- decrease speed", "- increase speed"};

	i = 2;
	wattron(hotkeys_info, COLOR_PAIR(C_BRIGHT_WHITE));
	wattron(hotkeys_info, A_BOLD);
	mvwprintw(hotkeys_info, i++, BEGIN_OF_LINE + 1, "Info On Hotkeys");
	wattroff(hotkeys_info, A_BOLD);
	i++;
	j = 0;
	while (j < NB_OF_KEYS)
		mvwprintw(hotkeys_info, i++, BEGIN_OF_LINE + 1, "%s", keys[j++]);
	i -= NB_OF_KEYS;
	j = 0;
	while (j < NB_OF_KEYS)
		mvwprintw(hotkeys_info, i++, BEGIN_OF_LINE + 15, "%s", values[j++]);
	wattroff(hotkeys_info, COLOR_PAIR(C_BRIGHT_WHITE));
	wrefresh(hotkeys_info);
}
