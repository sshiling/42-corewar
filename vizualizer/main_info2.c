/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_info2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noprysk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:24:53 by noprysk           #+#    #+#             */
/*   Updated: 2018/05/01 18:24:55 by noprysk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void				print_grey_line(WINDOW *main_info, int *j)
{
	wattron(main_info, COLOR_PAIR(BOARDER));
	(*j)++;
	mvwprintw(main_info, (*j)++, 1, "%0*d",
		NB_OF_COLUMNS_OF_MAIN_INFO - 2, 0);
	(*j)++;
	wattroff(main_info, COLOR_PAIR(BOARDER));
}

void				print_speed_bar(WINDOW *main_info, long speed, int j)
{
	int				active;
	int				i;

	mvwprintw(main_info, j, 19, "Speed: ");
	active = (SLOWEST_SPEED - speed) / SPEED_DELTA;
	wattron(main_info, COLOR_PAIR(C_ACTIVE_BAR));
	i = 0;
	while (i < active)
		mvwprintw(main_info, j, 26 + i++, "|");
	wattroff(main_info, COLOR_PAIR(C_ACTIVE_BAR));
	wattron(main_info, COLOR_PAIR(C_PASSIVE_BAR));
	i = 0;
	while (i < MAX_SLOTS - active)
		mvwprintw(main_info, j, 26 + active + i++, "|");
	wattroff(main_info, COLOR_PAIR(C_ACTIVE_BAR));
}

void				print_first_table(WINDOW *main_info, t_vm *vm, int *j)
{
	wattron(main_info, A_BOLD);
	mvwprintw(main_info, (*j)++, 3, "**  RUNNING **");
	print_speed_bar(main_info, vm->speed, *j - 1);
	mvwprintw(main_info, (*j)++, 3, "Cycle:          %i",
		vm->cycle);
	mvwprintw(main_info, (*j)++, 3, "Processes:      %i     ",
		vm->process_count);
	print_grey_line(main_info, j);
}

void				print_players(WINDOW *main_info, t_vm *vm, int *j)
{
	int				i;

	i = 0;
	while (i < vm->player_count)
	{
		wattron(main_info, COLOR_PAIR(vm->players[i].proc_count == 0
			? C_DEFAULT : C_DEFAULT + i + 1));
		mvwprintw(main_info, (*j)++, 3, "Player %i:      %.*s",
			vm->players[i].num % 10, MAX_LEN_OF_PLAYER, vm->players[i].name);
		mvwprintw(main_info, (*j)++, 3, "Last live:      %i     ",
			vm->players[i].last_live);
		mvwprintw(main_info, (*j)++, 3, "Lives in cp:    %i     ",
			vm->players[i].lives_in_cur_per);
		(*j)++;
		i++;
		wattroff(main_info, COLOR_PAIR(vm->players[i].proc_count == 0
			? C_DEFAULT : C_DEFAULT + i + 1));
	}
	(*j)--;
}
