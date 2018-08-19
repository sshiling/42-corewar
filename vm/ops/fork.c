/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:25:14 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void			op_fork(t_vm *vm, t_process *p, t_op *op)
{
	t_process		*fp;
	unsigned char	*pos;

	pos = get_pos(vm, op, (short)op->args[0]);
	fp = process_new(pos, p->r[1], p->player);
	ft_memcpy(fp, p, sizeof(*p));
	fp->next = NULL;
	fp->op.name = NULL;
	fp->pc = pos;
	fp->live = false;
	process_add(vm, &vm->proc_list, fp);
	set_color(vm, pos, vm_color(vm->vis[pos - vm->mem].color, C_PROCESS),
		BOLD_AGE);
}
