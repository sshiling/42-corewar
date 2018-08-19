/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:34:25 by vchornyi          #+#    #+#             */
/*   Updated: 2018/04/26 17:34:27 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		add_bytes(t_prog *prog, unsigned int value, int num_bytes)
{
	unsigned int	*p4;
	unsigned short	*p2;

	if (prog->idx + num_bytes > prog->memory_prog)
	{
		prog->memory_prog += PROG_MEMORY;
		prog->prog = (unsigned char *)realloc(prog->prog, prog->memory_prog);
		if (!prog->prog)
			exit(1);
	}
	if (num_bytes == 4)
	{
		p4 = (unsigned int *)&prog->prog[prog->idx];
		*p4 = reverse_bytes(value, 4);
		prog->idx += 4;
	}
	else if (num_bytes == 2)
	{
		p2 = (unsigned short *)&prog->prog[prog->idx];
		*p2 = (unsigned short)reverse_bytes(value, 2);
		prog->idx += 2;
	}
	else
		prog->prog[prog->idx++] = (unsigned char)value;
}

static void	add_bytes_and_label(t_op *op, t_prog *prog, int idx, int byte_size)
{
	char	*name;
	size_t	label_i;

	label_i = ft_strchr(op->args[idx], LABEL_CHAR) - op->args[idx];
	name = ft_strsub(op->args[idx], label_i + 1, ft_strlen(op->args[idx]) - 1);
	if (!name)
		exit(1);
	add_label(&prog->empty_labels, name, prog->idx, byte_size)->val = op->idx;
	add_bytes(prog, 0, byte_size);
}

static int	get_num(char *str)
{
	int		num;
	int		i;

	num = ft_atoi(str);
	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
			;
		else if (!ft_isdigit(str[i]))
			error("Wrong argument");
		i++;
	}
	return (num);
}

static int	check_reg_number(int reg_number)
{
	if (reg_number <= 0 || reg_number > REG_NUMBER)
		error("Wrong reg number");
	return (reg_number);
}

void		convert_arguments(t_op *op, t_prog *prog, t_op_tab *op_exp)
{
	int i;

	i = 0;
	while (i < op_exp->op_num)
	{
		if (op->arg_types[i] == T_REG)
			add_bytes(prog, check_reg_number(get_num(&op->args[i][1])), 1);
		else if (op->arg_types[i] == T_DIR)
		{
			if (op->args[i][1] != LABEL_CHAR)
				add_bytes(prog, get_num(&op->args[i][1]), op_exp->label_size);
			else
				add_bytes_and_label(op, prog, i, op_exp->label_size);
		}
		else if (op->arg_types[i] == T_IND)
		{
			if (op->args[i][0] != LABEL_CHAR)
				add_bytes(prog, get_num(op->args[i]), IND_SIZE);
			else
				add_bytes_and_label(op, prog, i, IND_SIZE);
		}
		i++;
	}
}
