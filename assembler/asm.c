/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshiling <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:14:29 by sshiling          #+#    #+#             */
/*   Updated: 2018/04/19 19:14:31 by sshiling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_file(t_prog *prog)
{
	t_file	*file;
	int		is_n;
	int		is_c;

	is_n = NAME_START;
	is_c = COMMENT_START;
	file = prog->file;
	while (file)
	{
		parse_one_file(file, prog, &is_n, &is_c);
		file = file->next;
	}
}

int			main(int argc, char **argv)
{
	t_prog	*prog;

	if (argc != 2)
		error("Usage: ./asm source_file.s");
	if (ft_strlen(argv[1]) <= 2
	|| !ft_strequ(&argv[1][ft_strlen(argv[1]) - 2], ".s"))
		error("Wrong file format, should be source_file.s");
	prog = init_prog();
	read_file(prog, argv[1]);
	parse_file(prog);
	if (prog->idx == 0 && !prog->labels)
		error("No instructions in file");
	fill_empty_labels(prog);
	prog->header->prog_size = reverse_bytes(prog->idx, 4);
	write_res_into_file(prog);
	return (0);
}
