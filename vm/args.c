/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:40:45 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:59:04 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static bool	set_argtype(unsigned int *argtype, int val)
{
	unsigned int	v;
	bool			res;

	v = (unsigned int)(val > 0 ? 1 << (val - 1) : 0);
	res = ((*argtype & v) == v && !(*argtype && !v)) || !*argtype;
	if (*argtype)
		*argtype = v;
	return (res);
}

bool		set_argstypes(t_vm *vm, t_process *p, t_op *op)
{
	bool res;

	res = true;
	pc_add(vm, p, 1);
	if (op->check_args)
	{
		res = set_argtype(&op->argtypes[0], ((*p->pc >> 6) & 3)) & res;
		res = set_argtype(&op->argtypes[1], ((*p->pc >> 4) & 3)) & res;
		res = set_argtype(&op->argtypes[2], ((*p->pc >> 2) & 3)) & res;
		pc_add(vm, p, 1);
	}
	return (res);
}

static bool	set_arg(t_vm *vm, t_process *p, t_op *op, int i)
{
	if (op->argtypes[i] == T_REG)
	{
		op->args[i] = *p->pc;
		pc_add(vm, p, 1);
		if (op->args[i] < 1 || op->args[i] > REG_NUMBER)
			return (false);
	}
	else if ((op->argtypes[i] == T_DIR && op->label_size == 2) ||
			(op->argtypes[i] == T_IND))
	{
		op->args[i] = read_pos(vm, p->pc) >> 16;
		pc_add(vm, p, 2);
	}
	else if (op->argtypes[i] == T_DIR && op->label_size == 4)
	{
		op->args[i] = read_pos(vm, p->pc);
		pc_add(vm, p, 4);
	}
	return (true);
}

bool		set_args(t_vm *vm, t_process *p, t_op *op)
{
	bool	res;
	int		i;

	res = set_argstypes(vm, p, op);
	i = -1;
	while (++i < 3)
		res = set_arg(vm, p, op, i) & res;
	return (res);
}
