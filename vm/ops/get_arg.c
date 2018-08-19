/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:23:50 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				get_arg(t_vm *vm, t_process *p, t_op *op, int i)
{
	unsigned char *pos;

	if (op->argtypes[i] == T_REG)
		return (p->r[op->args[i]]);
	if (op->argtypes[i] == T_DIR)
	{
		if (op->label_size == sizeof(int))
			return (op->args[i]);
		if (op->label_size == sizeof(short))
			return ((short)op->args[i]);
	}
	if (op->argtypes[i] == T_IND)
	{
		pos = get_pos(vm, op, (short)op->args[i]);
		return (read_pos(vm, pos));
	}
	return (0);
}
