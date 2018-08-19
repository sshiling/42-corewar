/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:24:08 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	*get_pos(t_vm *vm, t_op *op, short off)
{
	int				shift;
	unsigned char	*pos;

	if (op->is_long)
		shift = off;
	else
		shift = off % IDX_MOD;
	shift = (op->pc - vm->mem + shift) % MEM_SIZE;
	if (shift < 0)
		shift = MEM_SIZE + shift;
	pos = vm->mem + shift;
	return (pos);
}

int				read_pos(t_vm *vm, unsigned char *pos)
{
	int res;
	int off;

	res = 0;
	off = (pos - vm->mem) % MEM_SIZE;
	res |= vm->mem[off] << 24;
	res |= vm->mem[(off + 1) % MEM_SIZE] << 16;
	res |= vm->mem[(off + 2) % MEM_SIZE] << 8;
	res |= vm->mem[(off + 3) % MEM_SIZE];
	return (res);
}

void			write_pos(t_vm *vm, unsigned char *pos, int val)
{
	int off;

	off = (pos - vm->mem) % MEM_SIZE;
	vm->mem[off] = (unsigned char)(val >> 24);
	vm->mem[(off + 1) % MEM_SIZE] = (unsigned char)(val >> 16);
	vm->mem[(off + 2) % MEM_SIZE] = (unsigned char)(val >> 8);
	vm->mem[(off + 3) % MEM_SIZE] = (unsigned char)val;
}
