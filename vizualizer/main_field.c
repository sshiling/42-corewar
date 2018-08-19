/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noprysk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:44:23 by noprysk           #+#    #+#             */
/*   Updated: 2018/04/20 18:44:24 by noprysk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void			update_converted_array(t_vm *vm)
{
	int					j;
	int					i;
	int					q;
	int					num;
	static const char	base_str[BASE] = "0123456789abcdef";

	j = 0;
	i = 0;
	while (i < MEM_SIZE)
	{
		vm->converted_array[j + LEN_OF_NBR] = ' ';
		num = vm->mem[i];
		q = LEN_OF_NBR - 1;
		while (q >= 0)
		{
			vm->converted_array[j + q] = base_str[num % BASE];
			num = num / BASE;
			q--;
		}
		j += LEN_OF_NBR + 1;
		i++;
	}
	vm->converted_array[j] = '\0';
}

static void		set_color_(WINDOW *main_field, t_vm *vm, int q)
{
	if (((vm->vis)[q]).age != NOT_BOLD)
	{
		wattron(main_field, A_BOLD);
		(vm->vis)[q].age--;
	}
	if (((vm->vis)[q]).blink > 0)
	{
		((vm->vis)[q]).blink--;
		wattron(main_field, COLOR_PAIR(C_DEAD_PROCESS));
	}
	else
		wattron(main_field, COLOR_PAIR(((vm->vis)[q]).color));
}

static void		off_attributes_(WINDOW *main_field, t_vm *vm, int q)
{
	wattroff(main_field, COLOR_PAIR(((vm->vis)[q]).color));
	wattroff(main_field, A_BOLD);
}

void			refresh_main_field(WINDOW *main_field, t_vm *vm)
{
	int			i;
	int			j;
	int			p;
	int			q;

	update_converted_array(vm);
	i = 1;
	j = 1;
	p = 0;
	q = 0;
	while (q < MEM_SIZE)
	{
		set_color_(main_field, vm, q);
		mvwprintw(main_field, i, j++, "%c", vm->converted_array[p++]);
		mvwprintw(main_field, i, j++, "%c", vm->converted_array[p++]);
		off_attributes_(main_field, vm, q);
		mvwprintw(main_field, i, j++, "%c", vm->converted_array[p++]);
		if ((j - 1) % CHARS_IN_LINE == 0)
		{
			j = 1;
			i++;
		}
		q++;
	}
	wrefresh(main_field);
}
