/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 15:43:13 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 18:24:03 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "corewar.h"
#include "libft.h"

unsigned int	reverse_bytes(unsigned int num, int size)
{
	unsigned int	reverse_num;
	int				i;

	i = -1;
	reverse_num = 0;
	while (++i < size)
		reverse_num |= ((num >> 8 * i) & UCHAR_MAX) << 8 * (size - i - 1);
	return (reverse_num);
}

static void		init_corewar(t_vm *vm, int argc, char *argv[])
{
	ft_bzero(vm, sizeof(*vm));
	init_params(&vm->p);
	set_params(&vm->p, argc, argv);
	if (!vm->p.i)
		exit_usage();
	load_vm(vm, vm->p.i, vm->p.champ_names, vm->p.champ_nums);
}

int				main(int argc, char *argv[])
{
	t_vm		vm;

	init_corewar(&vm, argc, argv);
	if (vm.p.mode == NCURSES_MODE)
	{
		while (exec_ncurses(&vm))
			init_corewar(&vm, argc, argv);
	}
	else if (vm.p.mode == DUMP_MODE || vm.p.mode == S_MODE)
		exec_dump(&vm, vm.p.mode == DUMP_MODE);
	else if (vm.p.mode == V_MODE)
		exec_v(&vm);
	else
		exec_basic(&vm);
	return (0);
}
