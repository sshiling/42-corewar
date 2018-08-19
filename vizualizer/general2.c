/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noprysk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:54:45 by noprysk           #+#    #+#             */
/*   Updated: 2018/05/01 17:54:47 by noprysk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void			refresh_all(WINDOW **windows, t_vm *vm)
{
	refresh_main_field(windows[MAIN_FIELD], vm);
	refresh_main_info(windows[MAIN_INFO], vm);
	refresh_process_info(windows[PROCESS_INFO], vm, UPDATE_PROCESS_INFO);
}

void			print_pause(WINDOW *main_info)
{
	wattron(main_info, A_BOLD);
	mvwprintw(main_info, 2, 3, "**  PAUSED  **");
	wattroff(main_info, A_BOLD);
	wrefresh(main_info);
}

void			print_end(WINDOW *main_info)
{
	wattron(main_info, A_BOLD);
	mvwprintw(main_info, 2, 3, "**  END     **");
	wattroff(main_info, A_BOLD);
	wrefresh(main_info);
}

int				wait_for_reply(WINDOW *main_field)
{
	int					key;
	int					i;
	static const int	keys[NB_OF_KEYS] = {SPACE, ONE, TEN, HUNDRED,
		FIVE_HUNDRED, ESCAPE, KEY_MOUSE, REAPEAT, DECREASE_SPEED,
		INCRESAE_SPEED};
	static const int	returns[NB_OF_KEYS] = {SPACE_RETURN, 1, 10, 100, 500,
		ESC_RETURN, MOUSE_RETURN, REPEAT_RETURN, DECREASE_SPEED_RETURN,
		INCRESAE_SPEED_RETURN};

	nodelay(main_field, FALSE);
	while (1)
	{
		key = wgetch(main_field);
		i = 0;
		while (i < NB_OF_KEYS)
		{
			if (key == keys[i])
			{
				nodelay(main_field, TRUE);
				return (returns[i]);
			}
			i++;
		}
	}
}

bool			check_if_repeat(WINDOW *main_field)
{
	int			key;

	while (1)
	{
		key = wgetch(main_field);
		if (key == ESCAPE)
			return (false);
		if (key == REAPEAT)
			return (true);
	}
}
