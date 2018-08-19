# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 12:15:05 by vchornyi          #+#    #+#              #
#    Updated: 2018/04/20 12:15:06 by vchornyi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_NAME = asm
VM_NAME = corewar

FLAGS = -Wall -Wextra -Werror
INC = -Iincludes/ -I$(LIB_DIR)/includes

ASM_SRC_NAME =  assembler/asm.c\
                assembler/init_structs.c\
                assembler/read.c\
                assembler/parse.c\
                assembler/get_header.c\
                assembler/op.c\
                assembler/convert.c\
                assembler/write.c\
                assembler/labels.c\
                assembler/convert_args.c

ASM_OBJ_NAME = $(ASM_SRC_NAME:.c=.o)
ASM_OBJ = $(addprefix $(OBJ_DIR),$(ASM_OBJ_NAME))

VM_SRC_NAME = vm/main.c\
	 vm/exit.c\
	 vm/params/params.c\
	 vm/params/params_funcs.c\
	 vm/args.c\
	 vm/corewar.c\
	 vm/load.c\
	 vm/op.c\
	 vm/process.c\
	 vm/vm_params.c\
	 vm/print_v.c\
	 vm/exec/exec.c\
	 vm/exec/exec_nc.c\
	 vm/exec/exec_proc.c\
	 vm/ops/add.c\
	 vm/ops/aff.c\
	 vm/ops/and.c\
	 vm/ops/fork.c\
	 vm/ops/get_arg.c\
	 vm/ops/ld.c\
	 vm/ops/ldi.c\
	 vm/ops/live.c\
	 vm/ops/lld.c\
	 vm/ops/lldi.c\
	 vm/ops/or.c\
	 vm/ops/pos.c\
	 vm/ops/set_color.c\
	 vm/ops/st.c\
	 vm/ops/sti.c\
	 vm/ops/sub.c\
	 vm/ops/xor.c\
	 vm/ops/zjmp.c\
	 vizualizer/process_info.c\
	 vizualizer/hotkeys_info.c\
	 vizualizer/general1.c\
	 vizualizer/general2.c\
	 vizualizer/main_field.c\
	 vizualizer/main_info1.c\
	 vizualizer/main_info2.c

VM_OBJ_NAME = $(VM_SRC_NAME:.c=.o)
VM_OBJ = $(addprefix $(OBJ_DIR),$(VM_OBJ_NAME))

LIB_DIR = libft/
OBJ_DIR = objs/

all: $(ASM_NAME) $(VM_NAME)

$(ASM_NAME): $(ASM_OBJ)
	@make -C $(LIB_DIR) --silent
	@gcc -o $(ASM_NAME) $(ASM_OBJ) -L $(LIB_DIR) -lft
	@echo "##### asm compiling finished! #####"

$(VM_NAME): $(VM_OBJ)
	@make -C $(LIB_DIR) --silent
	@gcc -o $(VM_NAME) $(VM_OBJ) -L $(LIB_DIR) -lft -lncurses
	@echo "##### corewar compiling finished! #####"

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)/assembler
	@mkdir -p $(OBJ_DIR)/vm/params
	@mkdir -p $(OBJ_DIR)/vm/exec
	@mkdir -p $(OBJ_DIR)/vm/ops
	@mkdir -p $(OBJ_DIR)/vizualizer
	@echo "##### Creating" [ $@ ] " #####"
	@gcc $(FLAGS) -o $@ -c $< $(INC)

clean:
	@make -C $(LIB_DIR) clean  --silent
	@rm -f $(ASM_OBJ) $(VM_OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "##### Removed object files #####"

fclean: clean
	@make -C $(LIB_DIR) fclean  --silent
	@rm -f $(ASM_NAME) $(VM_NAME)
	@echo "##### Removed binary files #####"

re: fclean all

.PHONY: all clean fclean re