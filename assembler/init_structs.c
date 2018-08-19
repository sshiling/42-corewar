/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:21:51 by vchornyi          #+#    #+#             */
/*   Updated: 2018/04/20 13:21:52 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_header	*init_header(void)
{
	t_header	*header;

	header = (t_header *)malloc(sizeof(t_header));
	if (!header)
		exit(1);
	header->magic = reverse_bytes(COREWAR_EXEC_MAGIC, 4);
	header->prog_name[0] = '\0';
	header->prog_size = 0;
	header->comment[0] = '\0';
	return (header);
}

t_prog			*init_prog(void)
{
	t_prog	*prog;

	prog = (t_prog *)malloc(sizeof(t_prog));
	if (!prog)
		exit(1);
	prog->header = init_header();
	prog->prog = (unsigned char *)malloc(sizeof(unsigned char) * PROG_MEMORY);
	prog->memory_prog = PROG_MEMORY;
	if (!prog->prog)
		exit(1);
	prog->idx = 0;
	prog->file = NULL;
	prog->file_name = NULL;
	prog->labels = NULL;
	prog->empty_labels = NULL;
	return (prog);
}

t_file			*init_file(char *line)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		exit(1);
	file->line = line;
	file->next = NULL;
	return (file);
}

t_label			*init_label(char *name, unsigned int addr, int size)
{
	t_label	*label;

	label = (t_label *)malloc(sizeof(t_label));
	if (!label)
		exit(1);
	label->name = name;
	label->addr = addr;
	label->size = size;
	label->val = 0;
	label->next = NULL;
	return (label);
}

t_op			*init_op(void)
{
	t_op	*op;
	int		i;

	op = (t_op *)malloc(sizeof(t_op));
	if (!op)
		exit(1);
	op->name = NULL;
	op->args = (char **)malloc(sizeof(char *) * 4);
	if (!op->args)
		exit(1);
	i = 0;
	while (i < 4)
		op->args[i++] = NULL;
	op->arg_types = (t_arg_type *)malloc(sizeof(t_arg_type) * 4);
	ft_memset(op->arg_types, 0, 4);
	op->idx = 0;
	return (op);
}
