/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshiling <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:18:18 by sshiling          #+#    #+#             */
/*   Updated: 2018/04/23 15:18:20 by sshiling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_aligned_len(int len)
{
	return (((len + 1) % 4 == 0) ? 0 : (4 - (len + 1) % 4));
}

void		write_res_into_file(t_prog *prog)
{
	int		fd;
	char	*name;

	prog->file_name[ft_strlen(prog->file_name) - 2] = '\0';
	name = ft_strjoin(prog->file_name, ".cor");
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error("Create file error");
	ft_printf("Writing output program to %s\n", name);
	write(fd, prog->header, sizeof(prog->header->magic) + PROG_NAME_LENGTH + 1
	+ get_aligned_len(PROG_NAME_LENGTH) + sizeof(prog->header->prog_size)
	+ COMMENT_LENGTH + 1 + get_aligned_len(COMMENT_LENGTH));
	write(fd, prog->prog, prog->idx);
	ft_strdel(&name);
}
