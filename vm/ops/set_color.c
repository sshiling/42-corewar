/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:57:06 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	vm_color(unsigned int c, int type)
{
	if (c >= C_PROCESS_DEFAULT)
		c -= C_DIF;
	if (type == C_PROCESS)
		return (c + C_DIF);
	if (type == C_PLAYER)
		return (c);
	return (0);
}

void			set_color(t_vm *vm, void *pos, unsigned int color, int age)
{
	unsigned char	*cpos;
	long			i;

	cpos = pos;
	i = cpos - vm->mem;
	vm->vis[i].color = color;
	vm->vis[i].age = (unsigned)age;
}

void			set_color4(t_vm *vm, void *pos, unsigned int color, int age)
{
	unsigned char	*cpos;
	long			i;
	long			j;

	cpos = pos;
	i = cpos - vm->mem;
	j = -1;
	while (++j < 4)
	{
		vm->vis[(i + j) % MEM_SIZE].color = color;
		vm->vis[(i + j) % MEM_SIZE].age = (unsigned)age;
	}
}
