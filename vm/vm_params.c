/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 18:10:46 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void			kill_proc(t_vm *vm, t_process *p, bool *has_killed)
{
	if (!p->is_alive || vm->cycle_to_die <= 0)
	{
		process_kill(vm, &vm->proc_list, p);
		*has_killed = true;
	}
	else
	{
		p->live = 0;
		p->is_alive = false;
	}
}

static int			kill_zero_live(t_vm *vm)
{
	t_process	*p;
	t_process	*next;
	int			nbr_live;
	bool		has_killed;

	p = vm->proc_list;
	nbr_live = 0;
	has_killed = false;
	while (p)
	{
		p->player->lives_in_cur_per = 0;
		next = p->next;
		nbr_live += p->live;
		kill_proc(vm, p, &has_killed);
		p = next;
	}
	if (has_killed && vm->p.mode == NCURSES_MODE && !vm->p.step_by_step_mode)
		system("afplay kill.mp3");
	vm->nbr_live = nbr_live;
	return (nbr_live);
}

static inline bool	is_die_cycle(t_vm *vm)
{
	return (vm->cycle_to_die < 1 || vm->cycle_to_die == vm->period_cycle);
}

void				increment_cycle(t_vm *vm)
{
	++vm->cycle;
	++vm->period_cycle;
	if (is_die_cycle(vm))
	{
		vm->period_cycle = 0;
		++vm->check_count;
		if (kill_zero_live(vm) >= NBR_LIVE || vm->check_count == MAX_CHECKS)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			if (vm->p.arg.v & 2)
				ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
			vm->check_count = 0;
		}
	}
}
