/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:53:49 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 18:00:13 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void				exec_dump(t_vm *vm, bool exit_after_dump)
{
	introduce(vm);
	if (!vm->p.arg.n)
		dump(vm, exit_after_dump);
	else
		while (vm->proc_list)
		{
			update_info(vm);
			if (vm->cycle % vm->p.arg.n == 0 && vm->proc_list)
				dump(vm, exit_after_dump);
		}
	print_win(vm);
}

void				exec_v(t_vm *vm)
{
	introduce(vm);
	while (vm->proc_list)
	{
		if (vm->p.arg.v & 2)
			ft_printf("It is now cycle %d\n", vm->cycle + 1);
		update_info(vm);
	}
	print_win(vm);
}

void				exec_basic(t_vm *vm)
{
	introduce(vm);
	while (vm->proc_list)
		update_info(vm);
	print_win(vm);
}
