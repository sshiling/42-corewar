/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:54:03 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 18:04:49 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "vizualizer.h"
#include "libft.h"

static void			make_field_ready(WINDOW **windows, t_vm *vm)
{
	init_ncurses();
	open_windows(windows);
	nodelay(windows[MAIN_FIELD], TRUE);
	keypad(windows[MAIN_FIELD], TRUE);
	print_boarder(windows);
	print_hotkeys_info(windows[HOTKEYS_INFO]);
	print_pause(windows[MAIN_INFO]);
	refresh_all(windows, vm);
}

static bool			bring_field_to_the_end(WINDOW **windows,
						t_vm *vm, bool end, bool repeat_key)
{
	bool			repeat;

	if (end)
	{
		print_end(windows[MAIN_INFO]);
		system("afplay win.mp3");
	}
	nodelay(windows[MAIN_FIELD], FALSE);
	repeat = (end) ? check_if_repeat(windows[MAIN_FIELD]) : repeat_key;
	close_windows(windows);
	free_proc_list(&vm->proc_list);
	free(vm->players);
	return (repeat);
}

static int			process_reply(t_vm *vm, WINDOW *windows[], int reply)
{
	int i;

	if (reply == MOUSE_RETURN)
		refresh_process_info(windows[PROCESS_INFO], vm, FIND_PROCESS);
	else if (reply == ESC_RETURN || reply == REPEAT_RETURN)
		return (bring_field_to_the_end(windows, vm, NOT_END,
			reply == REPEAT_RETURN));
	else if (reply == SPACE_RETURN)
		vm->p.step_by_step_mode = false;
	else if (reply == DECREASE_SPEED_RETURN)
		vm->speed = (vm->speed + SPEED_DELTA > SLOWEST_SPEED) ?
		SLOWEST_SPEED : vm->speed + SPEED_DELTA;
	else if (reply == INCRESAE_SPEED_RETURN)
		vm->speed = (vm->speed - SPEED_DELTA >= 0) ?
		vm->speed - SPEED_DELTA : 0;
	else
	{
		i = -1;
		while (++i < reply)
			update_info(vm);
	}
	return (CONTINUE_CYCLE);
}

bool				exec_ncurses(t_vm *vm)
{
	WINDOW			*windows[NB_OF_WINDOWS];
	int				key;
	int				res;

	vm->speed = NORMAL_SPEED;
	make_field_ready(windows, vm);
	while (vm->proc_list)
	{
		key = wgetch(windows[MAIN_FIELD]);
		if (key == SPACE)
			vm->p.step_by_step_mode = !vm->p.step_by_step_mode;
		if (vm->p.step_by_step_mode)
		{
			print_pause(windows[MAIN_INFO]);
			if ((res =
				process_reply(vm, windows, wait_for_reply(windows[MAIN_FIELD])))
				!= CONTINUE_CYCLE)
				return (res);
		}
		else
			update_info(vm);
		usleep(vm->speed);
		refresh_all(windows, vm);
	}
	return (bring_field_to_the_end(windows, vm, END, false));
}
