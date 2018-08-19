/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:24:13 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void			op_st(t_vm *vm, t_process *p, t_op *op)
{
	unsigned int	val;
	unsigned char	*pos;
	unsigned int	color;

	if (op->argtypes[1] == T_REG)
	{
		p->r[op->args[1]] = p->r[op->args[0]];
	}
	else if (op->argtypes[1] == T_IND)
	{
		val = p->r[op->args[0]];
		pos = get_pos(vm, op, op->args[1]);
		write_pos(vm, pos, val);
		color = vm->vis[op->pc - vm->mem].color;
		set_color4(vm, pos, vm_color(color, C_PLAYER), BOLD_AGE);
	}
}
