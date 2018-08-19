/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:24:20 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_xor(t_vm *vm, t_process *p, t_op *op)
{
	op->args[0] = get_arg(vm, p, op, 0);
	op->args[1] = get_arg(vm, p, op, 1);
	p->r[op->args[2]] = op->args[0] ^ op->args[1];
	p->carry = !p->r[op->args[2]];
	op->argtypes[0] = T_DIR;
	op->argtypes[1] = T_DIR;
}
