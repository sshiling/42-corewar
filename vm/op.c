/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:34:36 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 18:08:39 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"

t_op const	g_ops[17] =
{
	{
		.func = NULL
	},
	{
		.name = "live",
		.func = op_live,
		.argtypes = {T_DIR, 0, 0},
		.cycles = 10,
		.check_args = 0,
		.label_size = 4,
		.is_long = false
	},
	{
		.name = "ld",
		.func = op_ld,
		.argtypes = {T_DIR | T_IND, T_REG, 0},
		.cycles = 5,
		.check_args = 1,
		.label_size = 4,
		.is_long = false
	},
	{
		.name = "st",
		.func = op_st,
		.argtypes = {T_REG, T_IND | T_REG, 0},
		.cycles = 5,
		.check_args = 1,
		.label_size = 4,
		.is_long = false
	},
	{
		.name = "add",
		.func = op_add,
		.argtypes = {T_REG, T_REG, T_REG},
		.cycles = 10,
		.check_args = 1,
		.label_size = 4,
		.is_long = false
	},
	{
		.name = "sub",
		.func = op_sub,
		.argtypes = {T_REG, T_REG, T_REG},
		.cycles = 10,
		.check_args = 1,
		.label_size = 4,
		.is_long = false
	},
	{
		.name = "and",
		.func = op_and,
		.argtypes = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.cycles = 6,
		.check_args = 1,
		.label_size = 4,
		.is_long = false
	},
	{
		.name = "or",
		.func = op_or,
		.argtypes = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.cycles = 6,
		.check_args = 1,
		.label_size = 4,
		.is_long = false
	},
	{
		.name = "xor",
		.func = op_xor,
		.argtypes = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.cycles = 6,
		.check_args = 1,
		.label_size = 4,
		.is_long = false
	},
	{
		.name = "zjmp",
		.func = op_zjmp,
		.argtypes = {T_DIR, 0, 0},
		.cycles = 20,
		.check_args = 0,
		.label_size = 2,
		.is_long = false
	},
	{
		.name = "ldi",
		.func = op_ldi,
		.argtypes = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.cycles = 25,
		.check_args = 1,
		.label_size = 2,
		.is_long = false
	},
	{
		.name = "sti",
		.func = op_sti,
		.argtypes = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.cycles = 25,
		.check_args = 1,
		.label_size = 2,
		.is_long = false
	},
	{
		.name = "fork",
		.func = op_fork,
		.argtypes = {T_DIR, 0, 0},
		.cycles = 800,
		.check_args = 0,
		.label_size = 2,
		.is_long = false
	},
	{
		.name = "lld",
		.func = op_lld,
		.argtypes = {T_DIR | T_IND, T_REG, 0},
		.cycles = 10,
		.check_args = 1,
		.label_size = 4,
		.is_long = true
	},
	{
		.name = "lldi",
		.func = op_lldi,
		.argtypes = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.cycles = 50,
		.check_args = 1,
		.label_size = 2,
		.is_long = true
	},
	{
		.name = "lfork",
		.func = op_fork,
		.argtypes = {T_DIR, 0, 0},
		.cycles = 1000,
		.check_args = 0,
		.label_size = 2,
		.is_long = true
	},
	{
		.name = "aff",
		.func = op_aff,
		.argtypes = {T_REG, 0, 0},
		.cycles = 2,
		.check_args = 1,
		.label_size = 4,
		.is_long = false
	}
};
