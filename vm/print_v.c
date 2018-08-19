/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_v.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:57:41 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 18:12:34 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		print_iarg(t_vm *vm, t_op *op)
{
	bool is_ldi;

	if ((is_ldi = ft_strequ(op->name, "ldi")) ||
		ft_strequ(op->name, "lldi"))
	{
		ft_printf(
			"       | -> load from %d + %d = %d (with pc %s%d)\n",
			op->args[0], op->args[1],
			op->args[0] + op->args[1],
			is_ldi ? "and mod " : "",
			op->res + op->pc - vm->mem);
	}
	else if (ft_strequ(op->name, "sti"))
		ft_printf(
			"       | -> store to %d + %d = %d (with pc and mod %d)\n",
			op->args[1], op->args[2],
			op->args[1] + op->args[2],
			op->res + op->pc - vm->mem);
}

static void		print_arg(t_op *op, int i)
{
	if (op->argtypes[i] == T_REG)
	{
		if (i == 1 && ft_strequ(op->name, "st"))
			ft_printf(" %d", op->args[i]);
		else
			ft_printf(" r%d", op->args[i]);
	}
	else if (op->argtypes[i] == T_DIR)
		ft_printf(" %d", op->label_size == 4 ?
						op->args[i] : (short)op->args[i]);
	else if (op->argtypes[i] == T_IND)
		ft_printf(" %d", ft_strequ(op->name, "ld") ?
						op->args[i] : (short)op->args[i]);
}

void			print_op(t_vm *vm, t_process *p, t_op *op)
{
	if (vm->p.arg.v & 4)
	{
		ft_printf("P %4d | ", p->num);
		ft_printf("%s", op->name);
		print_arg(op, 0);
		print_arg(op, 1);
		print_arg(op, 2);
		if (ft_strequ(op->name, "zjmp"))
			ft_printf(p->carry ? " OK" : " FAILED");
		if (ft_strequ(op->name, "fork"))
			ft_printf(" (%d)", ((short)op->args[0] % IDX_MOD
				+ op->pc - vm->mem));
		else if (ft_strequ(op->name, "lfork"))
			ft_printf(" (%d)", ((short)op->args[0] + op->pc - vm->mem));
		ft_printf("\n");
		print_iarg(vm, op);
	}
	if ((vm->p.arg.v & 1) && ft_strequ(op->name, "live") &&
		get_player(vm, op->args[0]))
		ft_printf("Player %d (%s) is said to be alive\n", -vm->winner,
				vm->players[-vm->winner - 1].name);
}

void			print_move(t_vm *vm, t_process *p)
{
	int len;
	int i;

	if ((vm->p.arg.v & 16) && (len = p->pc - p->op.pc)
		&& !(ft_strequ(p->op.name, "zjmp") && p->carry))
	{
		len = (len < 0 ? MEM_SIZE + len : len);
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ",
				len, p->op.pc - vm->mem, p->op.pc - vm->mem + len);
		i = -1;
		while (++i < len)
			ft_printf("%.2x ",
					vm->mem[(p->op.pc - vm->mem + i) % MEM_SIZE]);
		ft_printf("\n");
	}
}
