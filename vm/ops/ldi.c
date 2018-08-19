/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:23:55 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_ldi(t_vm *vm, t_process *p, t_op *op)
{
	op->args[0] = get_arg(vm, p, op, 0);
	op->args[1] = get_arg(vm, p, op, 1);
	op->res = ((int)op->args[0] + (int)op->args[1]) % IDX_MOD;
	p->r[op->args[2]] = read_pos(vm, get_pos(vm, op, op->res));
	op->label_size = 4;
	op->argtypes[0] = T_DIR;
	op->argtypes[1] = T_DIR;
}
