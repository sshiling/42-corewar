/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/04/27 17:14:19 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void			init_vm(t_vm *vm, int player_count)
{
	int i;

	i = -1;
	while (++i < MEM_SIZE)
		vm->vis[i].color = C_DEFAULT;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->player_count = player_count;
	vm->process_info_num = -1;
	if (player_count > MAX_PLAYERS)
		exit_error("too many players");
}

static void		set_player_color(t_vm *vm, int off, unsigned int i)
{
	unsigned int j;

	vm->players[i].i = i % C_COUNT + C_DEFAULT + 1;
	vm->vis[off].color = vm_color(vm->players[i].i, C_PROCESS);
	j = 0;
	while (++j < vm->players[i].prog_size)
		vm->vis[off + j].color = vm_color(vm->players[i].i, C_PLAYER);
}

static size_t	align_len(size_t len)
{
	return ((len + 1) % 4 == 0 ? 0 : 4 - (len + 1) % 4);
}

static void		load_player(int off, const char *name, t_player *p, t_vm *vm)
{
	int				fd;
	unsigned int	magic;
	char			align[3];
	ssize_t			ret;

	if ((fd = open(name, O_RDONLY)) < 0)
		exit_error("player read error");
	read(fd, &magic, sizeof(unsigned int));
	ret = read(fd, &p->name, PROG_NAME_LENGTH + 1);
	ret += read(fd, align, align_len(PROG_NAME_LENGTH));
	ret += read(fd, &p->prog_size, sizeof(unsigned int));
	ret += read(fd, &p->comment, COMMENT_LENGTH + 1);
	ret += read(fd, align, align_len(COMMENT_LENGTH));
	if (ret != (ssize_t)(PROG_NAME_LENGTH + 2 + align_len(PROG_NAME_LENGTH) +
		sizeof(unsigned int) + COMMENT_LENGTH + align_len(COMMENT_LENGTH)))
		exit_error("program too small");
	p->prog_size = reverse_bytes(p->prog_size, sizeof(unsigned int));
	if (read(fd, vm->mem + off, p->prog_size + 1) != p->prog_size)
		exit_error("code size differ from header");
	if (reverse_bytes(magic, sizeof(unsigned int)) != COREWAR_EXEC_MAGIC)
		exit_error("wrong player file format");
	if (p->prog_size > CHAMP_MAX_SIZE)
		exit_error("player program is too big");
	process_add(vm, &vm->proc_list, process_new(vm->mem + off, p->num, p));
	close(fd);
}

void			load_vm(t_vm *vm, int player_count,
						char **player_files, int *player_nums)
{
	int		i;
	int		off;

	i = -1;
	init_vm(vm, player_count);
	vm->players = ft_memalloc(sizeof(*vm->players) * player_count);
	while (++i < player_count)
	{
		off = i * (MEM_SIZE / player_count);
		vm->players[i].num = player_nums[i];
		vm->players[i].proc_count = 0;
		load_player(off, player_files[i], &vm->players[i], vm);
		set_player_color(vm, off, (unsigned)i);
	}
	vm->winner = vm->players[player_count - 1].num;
}
