/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:57:54 by noprysk           #+#    #+#             */
/*   Updated: 2018/05/02 12:52:52 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIZUALIZER_H
# define VIZUALIZER_H

# include <ncurses.h>
# include "../includes/op.h"
# include "../includes/corewar.h"

# define ROWS 64
# define COLUMNS 64
# define CHARS_IN_LINE 192
# define LEN_OF_NBR 2
# define BASE 16
# define SPACE 32
# define ONE 'q'
# define TEN 'w'
# define HUNDRED 'e'
# define FIVE_HUNDRED 'r'
# define NB_OF_COLUMNS_OF_MAIN_INFO 40
# define NB_OF_WINDOWS 4
# define NB_OF_KEYS 10
# define SPACE_RETURN 0
# define ESCAPE 27
# define ESC_RETURN -9
# define MOUSE_RETURN -123123
# define BEGIN_OF_LINE 2
# define MAX_LEN_OF_PLAYER 17
# define FIND_PROCESS true
# define UPDATE_PROCESS_INFO false
# define WHITE_COLOR 15
# define REAPEAT 'h'
# define REPEAT_RETURN 29292
# define END true
# define NOT_END false
# define DECREASE_SPEED 'z'
# define INCRESAE_SPEED 'x'
# define DECREASE_SPEED_RETURN 44444
# define INCRESAE_SPEED_RETURN 8888
# define SPEED_DELTA 20000
# define NORMAL_SPEED 50000
# define SLOWEST_SPEED 200000
# define MAX_SLOTS 10
# define CONTINUE_CYCLE 2

enum	e_window_defines { MAIN_FIELD, MAIN_INFO, PROCESS_INFO, HOTKEYS_INFO };

void	init_ncurses();
void	open_windows(WINDOW **windows);
void	close_windows(WINDOW **windows);
void	update_converted_array(t_vm *vm);
void	refresh_all(WINDOW **windows, t_vm *vm);
bool	check_if_repeat(WINDOW *main_field);
int		wait_for_reply(WINDOW *main_field);
void	print_pause(WINDOW *main_info);
void	print_end(WINDOW *main_info);

void	refresh_main_field(WINDOW *window, t_vm *vm);
void	refresh_main_info(WINDOW *main_info, t_vm *vm);
void	refresh_process_info(WINDOW *proc_info, t_vm *vm, bool fp);
void	print_hotkeys_info(WINDOW *hotkeys_info);
void	print_boarder(WINDOW **windows);
void	print_boarder_of_window(WINDOW *window);

void	print_grey_line(WINDOW *main_info, int *j);
void	print_speed_bar(WINDOW *main_info, long speed, int j);
void	print_first_table(WINDOW *main_info, t_vm *vm, int *j);
void	print_players(WINDOW *main_info, t_vm *vm, int *j);

#endif
