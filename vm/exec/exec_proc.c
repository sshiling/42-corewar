/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:56:43 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 18:02:01 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static inline bool	valid_opcode(unsigned char *pc)
{
	return (*pc > 0 && *pc < 0x11);
}

static void			exec_op(t_vm *vm, t_process *p)
{
	if (!--p->op.cycles)
	{
		if (set_args(vm, p, &p->op))
		{
			p->op.func(vm, p, &p->op);
			if (vm->p.aff_works || !ft_strequ(p->op.name, "aff"))
				print_op(vm, p, &p->op);
		}
		print_move(vm, p);
		p->op.name = NULL;
	}
}

void				exec_proc(t_vm *vm, t_process *p)
{
	if (p->op.name)
		exec_op(vm, p);
	else if (!valid_opcode(p->pc))
	{
		p->op.pc = p->pc;
		pc_add(vm, p, 1);
	}
	else
	{
		p->op = g_ops[*p->pc];
		p->op.pc = p->pc;
		exec_op(vm, p);
	}
	set_color(vm, p->op.pc,
			vm_color(vm->vis[p->op.pc - vm->mem].color, C_PLAYER), 0);
	set_color(vm, p->pc,
			vm_color(vm->vis[p->pc - vm->mem].color, C_PROCESS), 0);
}
