/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 13:20:16 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void		process_add(t_vm *vm, t_process **alst, t_process *proc)
{
	++vm->process_count;
	if (proc)
	{
		proc->num = ++vm->all_process_count;
		proc->next = *alst;
		*alst = proc;
	}
}

t_process	*process_new(unsigned char *pc, int player_num, t_player *pl)
{
	t_process *p;

	p = ft_memalloc(sizeof(*p));
	p->pc = pc;
	p->player = pl;
	p->r[1] = player_num;
	++pl->proc_count;
	return (p);
}

static void	process_kill_vis(t_vm *vm, t_process *p)
{
	if (vm->p.arg.v & 8)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				p->num, vm->cycle - p->last_live,
				vm->cycle_to_die);
	vm->vis[p->pc - vm->mem].color =
		vm_color(vm->vis[p->pc - vm->mem].color, C_PLAYER);
	--p->player->proc_count;
	vm->vis[p->pc - vm->mem].blink = BLINK_COUNT;
	if (vm->process_info_num == p->num)
		vm->process_info_num = -1;
	free(p);
}

void		process_kill(t_vm *vm, t_process **alst, t_process *proc)
{
	t_process *cur;

	--vm->process_count;
	cur = *alst;
	if (cur == proc)
	{
		*alst = cur->next;
		process_kill_vis(vm, proc);
	}
	else
	{
		while (cur->next)
		{
			if (cur->next == proc)
			{
				cur->next = cur->next->next;
				process_kill_vis(vm, proc);
				return ;
			}
			cur = cur->next;
		}
	}
}

void		free_proc_list(t_process **head)
{
	t_process	*cursor;
	t_process	*temp;

	cursor = *head;
	while (cursor)
	{
		temp = cursor->next;
		free(cursor);
		cursor = temp;
	}
	*head = NULL;
}
