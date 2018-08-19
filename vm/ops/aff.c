/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:23:28 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void			op_aff(t_vm *vm, t_process *p, t_op *op)
{
	if (vm->p.aff_works && vm->p.mode != NCURSES_MODE)
	{
		ft_putstr("Aff: ");
		ft_putchar((char)p->r[op->args[0]]);
		ft_putchar('\n');
	}
}
