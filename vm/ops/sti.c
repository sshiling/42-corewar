/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:24:16 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_sti(t_vm *vm, t_process *p, t_op *op)
{
	unsigned char	*pos;
	unsigned int	color;

	op->args[1] = get_arg(vm, p, op, 1);
	op->args[2] = get_arg(vm, p, op, 2);
	op->res = ((int)op->args[1] + (int)op->args[2]) % IDX_MOD;
	pos = get_pos(vm, op, op->res);
	write_pos(vm, pos, p->r[op->args[0]]);
	color = vm->vis[op->pc - vm->mem].color;
	set_color4(vm, pos, vm_color(color, C_PLAYER), BOLD_AGE);
	op->label_size = 4;
	op->argtypes[1] = T_DIR;
	op->argtypes[2] = T_DIR;
}
