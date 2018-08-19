/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_info1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noprysk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:24:31 by noprysk           #+#    #+#             */
/*   Updated: 2018/05/01 18:24:33 by noprysk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

static void		print_third_table(WINDOW *main_info, t_vm *vm, int *j)
{
	mvwprintw(main_info, (*j)++, 3, "Cycle to die:   %i     ",
		(vm->cycle_to_die < 0) ? 0 : vm->cycle_to_die);
	mvwprintw(main_info, (*j)++, 3, "Cycle delta:    %i      ", CYCLE_DELTA);
	mvwprintw(main_info, (*j)++, 3, "Nbr live:       %i      ", vm->nbr_live);
	mvwprintw(main_info, (*j)++, 3, "Max checks:     %i      ", MAX_CHECKS);
}

static void		print_winner(WINDOW *main_info, t_vm *vm, int *j)
{
	wattron(main_info, COLOR_PAIR(get_player(vm, vm->winner)->i));
	wattron(main_info, A_BOLD);
	(vm->cycle_to_die > 0 && vm->process_count != 0)
	? mvwprintw(main_info, (*j), 3, "Current winner: %-*.*s",
		MAX_LEN_OF_PLAYER, MAX_LEN_OF_PLAYER, get_player(vm, vm->winner)->name)
	: mvwprintw(main_info, (*j), 3, "Final winner:   %-*.*s",
		MAX_LEN_OF_PLAYER, MAX_LEN_OF_PLAYER, get_player(vm, vm->winner)->name);
	wattroff(main_info, A_BOLD);
	wattroff(main_info, COLOR_PAIR(get_player(vm, vm->winner)->i));
}

void			refresh_main_info(WINDOW *main_info, t_vm *vm)
{
	int			j;

	j = BEGIN_OF_LINE;
	print_first_table(main_info, vm, &j);
	print_players(main_info, vm, &j);
	print_grey_line(main_info, &j);
	print_third_table(main_info, vm, &j);
	print_grey_line(main_info, &j);
	print_winner(main_info, vm, &j);
	wrefresh(main_info);
}
