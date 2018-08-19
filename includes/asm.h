/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshiling <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:13:02 by sshiling          #+#    #+#             */
/*   Updated: 2018/04/19 19:13:08 by sshiling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"
# include <limits.h>

# define IS_WHITE_SPACE(x) ((x) == ' ' || ((x) >= 9 && (x) <= 13))
# define PROG_MEMORY 100

# define NAME_CONTINUE 0
# define NAME_START 1
# define NAME_END 2
# define COMMENT_CONTINUE 3
# define COMMENT_START 4
# define COMMENT_END 5
# define CMNT_CHAR ';'

typedef struct s_prog	t_prog;
typedef struct s_file	t_file;
typedef struct s_op		t_op;
typedef struct s_op_tab	t_op_tab;
typedef struct s_label	t_label;

struct			s_prog
{
	t_header		*header;
	unsigned char	*prog;
	unsigned int	memory_prog;
	unsigned int	idx;
	t_file			*file;
	char			*file_name;
	t_label			*labels;
	t_label			*empty_labels;
};

struct			s_file
{
	char	*line;
	t_file	*next;
};

struct			s_op
{
	char			*name;
	char			**args;
	t_arg_type		*arg_types;
	unsigned int	idx;
};

struct			s_label
{
	char			*name;
	unsigned int	addr;
	unsigned int	val;
	int				size;
	t_label			*next;
};

struct			s_op_tab
{
	char			*name;
	int				op_num;
	t_arg_type		op[3];
	unsigned char	opcode;
	int				cycles;
	char			*description;
	int				codage;
	int				carry;
	int				label_size;
};

extern t_op_tab	g_op_tab[17];

unsigned int	reverse_bytes(unsigned int num, int size);
void			convert_operations(t_op *op, t_prog *prog);
void			add_bytes(t_prog *prog, unsigned int value, int num_bytes);
void			convert_arguments(t_op *op, t_prog *prog, t_op_tab *op_exp);
t_prog			*init_prog(void);
t_file			*init_file(char *line);
t_label			*init_label(char *name, unsigned int addr, int size);
t_op			*init_op(void);
t_label			*add_label(t_label **label, char *name,
							unsigned int addr, int size);
int				is_label(char *line, t_prog *prog);
void			fill_empty_labels(t_prog *prog);
t_op_tab		*get_op_tab_by_name(char *name);
void			error(char *error_message);
void			read_file(t_prog *prog, char *file_name);
void			parse_one_file(t_file *file, t_prog *prog,
							int *is_n, int *is_c);
int				parse_name_comment(char *to, char *from, int max_len, int key);
void			write_res_into_file(t_prog *prog);

#endif
