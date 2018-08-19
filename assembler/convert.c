/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:42:28 by vchornyi          #+#    #+#             */
/*   Updated: 2018/04/23 15:42:30 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int			reverse_bytes(unsigned int num, int size)
{
	unsigned int	reverse_num;
	int				i;

	i = -1;
	reverse_num = 0;
	while (++i < size)
		reverse_num |= ((num >> 8 * i) & UCHAR_MAX) << 8 * (size - i - 1);
	return (reverse_num);
}

static unsigned char	get_codage(t_op *op)
{
	unsigned char	val;
	unsigned int	i;

	val = 0;
	i = 0;
	while (i < 3)
	{
		if (op->arg_types[i] && op->arg_types[i] == T_REG)
			val |= REG_CODE;
		else if (op->arg_types[i] && op->arg_types[i] == T_DIR)
			val |= DIR_CODE;
		else if (op->arg_types[i] && op->arg_types[i] == T_IND)
			val |= IND_CODE;
		val <<= 2;
		i++;
	}
	return (val);
}

static void				set_argument_type(t_op *op, t_op_tab *op_exp)
{
	int i;

	i = 0;
	while (op->args[i])
	{
		if (i > op_exp->op_num - 1)
			error("Wrong number of arguments");
		if (op->args[i][0] == 'r')
			op->arg_types[i] = T_REG;
		else if (op->args[i][0] == DIRECT_CHAR)
			op->arg_types[i] = T_DIR;
		else
			op->arg_types[i] = T_IND;
		if (!(op->arg_types[i] & op_exp->op[i]))
			error("Wrong type of argument");
		i++;
	}
	if (i != op_exp->op_num)
		error("Wrong number of arguments");
}

static void				delete_op(t_op *op)
{
	int i;

	free(op->arg_types);
	i = 0;
	while (i < 4)
		free(op->args[i++]);
	free(op->args);
	free(op->name);
	free(op);
}

void					convert_operations(t_op *op, t_prog *prog)
{
	t_op_tab *op_exp;

	op_exp = get_op_tab_by_name(op->name);
	if (!op_exp)
		error("Invalid instruction");
	set_argument_type(op, op_exp);
	op->idx = prog->idx;
	add_bytes(prog, op_exp->opcode, 1);
	if (op_exp->codage == 1)
		add_bytes(prog, get_codage(op), 1);
	convert_arguments(op, prog, op_exp);
	delete_op(op);
}
