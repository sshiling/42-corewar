/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:49:16 by noprysk           #+#    #+#             */
/*   Updated: 2018/05/02 12:51:07 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

static t_process	*process_get(t_vm *vm, int i)
{
	t_process *p;

	p = vm->proc_list;
	while (p)
	{
		if (p->pc - vm->mem == i)
			return (p);
		p = p->next;
	}
	return (NULL);
}

static t_process	*process_get_by_num(t_vm *vm, int num)
{
	t_process *p;

	p = vm->proc_list;
	while (p)
	{
		if (p->num == num)
			return (p);
		p = p->next;
	}
	return (NULL);
}

static void			print_registers(WINDOW *pi, t_process *p, int i)
{
	int					j;
	int					q;

	j = 1;
	q = BEGIN_OF_LINE;
	while (j <= REG_NUMBER)
	{
		mvwprintw(pi, i++, q, "%2i. %.2x %.2x %.2x %.2x",
		j, (unsigned char)(p->r[j] >> 24), (unsigned char)(p->r[j] >> 16),
		(unsigned char)(p->r[j] >> 8), (unsigned char)p->r[j]);
		if (j == REG_NUMBER / 2)
		{
			q += 17;
			i -= j;
		}
		j++;
	}
}

static int			define_process_index(int y, int x)
{
	return (((y - 1) * 64) + (x / 3));
}

void				refresh_process_info(WINDOW *pi, t_vm *vm, bool fp)
{
	t_process			*p;
	MEVENT				event;

	p = (fp && getmouse(&event) == OK)
	? process_get(vm, define_process_index(event.y, event.x))
	: process_get_by_num(vm, vm->process_info_num);
	if (!p)
	{
		werase(pi);
		print_boarder_of_window(pi);
		wattron(pi, COLOR_PAIR(C_BRIGHT_WHITE));
		mvwprintw(pi, 2, BEGIN_OF_LINE + 1,
			"Click on process to see its info  ");
		wattroff(pi, COLOR_PAIR(C_BRIGHT_WHITE));
	}
	else
	{
		vm->process_info_num = p->num;
		wattron(pi, COLOR_PAIR(C_BRIGHT_WHITE));
		mvwprintw(pi, 2, BEGIN_OF_LINE + 1,
			"Info on registers of process %3.3i", p->num);
		print_registers(pi, p, 4);
		wattroff(pi, COLOR_PAIR(C_BRIGHT_WHITE));
	}
	wrefresh(pi);
}
