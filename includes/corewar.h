/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 16:37:31 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 18:18:41 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "op.h"
# include <stdbool.h>

enum	e_color { C_DEFAULT = 1, C_PLAYER1, C_PLAYER2, C_PLAYER3, C_PLAYER4,
	C_PROCESS_DEFAULT, C_PROCESS_P1, C_PROCESS_P2, C_PROCESS_P3, C_PROCESS_P4,
	BOARDER, C_BRIGHT_WHITE, C_DEAD_PROCESS, C_ACTIVE_BAR, C_PASSIVE_BAR};
enum	e_mode_defines {NCURSES_MODE, DUMP_MODE,
	V_MODE, S_MODE, A_MODE, BASIC_MODE};

# define COLOR_GREY 8
# define BOLD_AGE 50
# define NOT_BOLD 0
# define C_COUNT 4
# define C_DIF 5
# define C_PROCESS 0
# define C_PLAYER 1
# define ROWS 64
# define CHARS_IN_LINE 192
# define BLINK_COUNT 500
# define NB_OF_MODES 4
# define NB_OF_FLAGS 5

typedef struct s_vm			t_vm;
typedef struct s_process	t_process;
typedef struct s_player		t_player;
typedef struct s_op			t_op;
typedef struct s_visual		t_visual;
typedef struct s_flags		t_flags;
typedef struct s_params		t_params;

struct			s_visual
{
	unsigned int	color;
	unsigned int	age;
	int				blink;
};

struct			s_flags
{
	int			v;
	int			n;
};

struct			s_params
{
	int				i;
	int				mode;
	t_flags			arg;
	bool			aff_works;
	int				champ_custom_num[MAX_PLAYERS];
	int				champ_nums[MAX_PLAYERS];
	char			*champ_names[MAX_PLAYERS];
	bool			step_by_step_mode;
};

struct			s_vm
{
	unsigned char	mem[MEM_SIZE];
	char			converted_array[(ROWS * CHARS_IN_LINE) + 1];
	t_visual		vis[MEM_SIZE];
	t_player		*players;
	t_process		*proc_list;
	unsigned int	cycle;
	int				period_cycle;
	int				cycle_to_die;
	int				winner;
	int				nbr_live;
	int				player_count;
	int				process_count;
	int				all_process_count;
	int				process_info_num;
	unsigned int	check_count;
	t_params		p;
	long			speed;
};

struct			s_op
{
	char			*name;
	void			(*func)(t_vm *vm, t_process *p, t_op *op);
	unsigned int	cycles;
	unsigned int	label_size;
	bool			check_args;
	bool			is_long;
	unsigned int	argtypes[3];
	unsigned int	args[3];
	int				res;
	unsigned char	*pc;
};

struct			s_process
{
	t_player		*player;
	t_process		*next;
	unsigned char	*pc;
	t_op			op;
	int				r[REG_NUMBER + 1];
	int				carry;
	int				live;
	bool			is_alive;
	int				last_live;
	int				num;
};

struct			s_player
{
	int				num;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned int	prog_size;
	int				last_live;
	int				lives_in_cur_per;
	int				proc_count;
	int				i;
};

extern t_op const	g_ops[17];

void			load_vm(t_vm *vm, int player_count, char **pl_fs, int *pl_nms);
void			exec_basic(t_vm *vm);

void			exec_dump(t_vm *vm, bool exit_after_dump);
bool			exec_ncurses(t_vm *vm);
void			exec_v(t_vm *vm);

void			introduce(t_vm *vm);
void			print_win(t_vm *vm);
void			dump(t_vm *vm, bool exit_after_dump);
void			update_info(t_vm *vm);
void			exec_proc(t_vm *vm, t_process *p);
void			increment_cycle(t_vm *vm);

void			print_move(t_vm *vm, t_process *p);
void			print_op(t_vm *vm, t_process *p, t_op *op);

void			process_add(t_vm *vm, t_process **alst, t_process *proc);
t_process		*process_new(unsigned char *pc, int player_num, t_player *pl);
void			process_kill(t_vm *vm, t_process **alst, t_process *proc);
void			pc_add(t_vm *vm, t_process *p, int val);
void			free_proc_list(t_process **head);

bool			set_args(t_vm *vm, t_process *p, t_op *op);
void			set_params(t_params *p, int argc, char *argv[]);
void			set_player_num(t_params *p, int i);
int				set_custom_player(t_params *p, int argc, char *argv[], int i);
void			define_player(t_params *p, int argc, char **argv, int i);
int				define_mode(t_params *p, int argc, char **argv, int i);
int				get_int(const char *str);
void			init_params(t_params *p);

unsigned int	reverse_bytes(unsigned int num, int size);
void			exit_error(char *message);
void			exit_usage(void);

int				get_arg(t_vm *vm, t_process *p, t_op *op, int i);
unsigned char	*get_pos(t_vm *vm, t_op *op, short off);
int				read_pos(t_vm *vm, unsigned char *pos);
void			write_pos(t_vm *vm, unsigned char *pos, int val);
unsigned int	vm_color(unsigned int c, int type);
void			set_color(t_vm *vm, void *pos, unsigned int color, int age);
void			set_color4(t_vm *vm, void *pos, unsigned int color, int age);
t_player		*get_player(t_vm *vm, int n);

void			op_live(t_vm *vm, t_process *p, t_op *op);
void			op_ld(t_vm *vm, t_process *p, t_op *op);
void			op_st(t_vm *vm, t_process *p, t_op *op);
void			op_add(t_vm *vm, t_process *p, t_op *op);
void			op_sub(t_vm *vm, t_process *p, t_op *op);
void			op_and(t_vm *vm, t_process *p, t_op *op);
void			op_or(t_vm *vm, t_process *p, t_op *op);
void			op_xor(t_vm *vm, t_process *p, t_op *op);
void			op_zjmp(t_vm *vm, t_process *p, t_op *op);
void			op_ldi(t_vm *vm, t_process *p, t_op *op);
void			op_sti(t_vm *vm, t_process *p, t_op *op);
void			op_fork(t_vm *vm, t_process *p, t_op *op);
void			op_lld(t_vm *vm, t_process *p, t_op *op);
void			op_lldi(t_vm *vm, t_process *p, t_op *op);
void			op_aff(t_vm *vm, t_process *p, t_op *op);

#endif
