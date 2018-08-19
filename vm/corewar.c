/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 18:06:22 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "vizualizer.h"
#include "libft.h"

void		pc_add(t_vm *vm, t_process *p, int val)
{
	p->pc = vm->mem + (p->pc - vm->mem + val) % MEM_SIZE;
}

void		introduce(t_vm *vm)
{
	int i;

	ft_printf("Introducing contestants...\n");
	i = -1;
	while (++i < vm->player_count)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				-vm->players[i].num,
				vm->players[i].prog_size,
				vm->players[i].name,
				vm->players[i].comment);
	}
}

void		print_win(t_vm *vm)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",
			-vm->winner,
			get_player(vm, vm->winner)->name);
}

void		dump(t_vm *vm, bool exit_after_dump)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (++i < 64)
	{
		j = -1;
		ft_printf("0x%0.4x : ", i * 64);
		while (++j < 64)
			ft_printf("%.2x ", vm->mem[i * 64 + j]);
		ft_printf("\n");
	}
	if (exit_after_dump)
	{
		exit(0);
	}
	else if (!vm->cycle)
	{
		print_win(vm);
		exit(0);
	}
	read(0, &c, 1);
}

void		update_info(t_vm *vm)
{
	t_process *p;

	p = vm->proc_list;
	while (p)
	{
		exec_proc(vm, p);
		p = p->next;
	}
	increment_cycle(vm);
}
