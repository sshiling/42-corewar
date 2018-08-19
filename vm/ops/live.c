/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:11:57 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 15:23:57 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

t_player		*get_player(t_vm *vm, int n)
{
	int i;

	i = -1;
	while (++i < vm->player_count)
		if (vm->players[i].num == n)
			return (&vm->players[i]);
	return (NULL);
}

void			op_live(t_vm *vm, t_process *p, t_op *op)
{
	++p->player->lives_in_cur_per;
	++p->live;
	p->is_alive = true;
	p->last_live = vm->cycle + 1;
	p->player->last_live = vm->cycle + 1;
	if (get_player(vm, op->args[0]))
		vm->winner = op->args[0];
}
