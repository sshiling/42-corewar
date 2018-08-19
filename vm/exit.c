/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:22:14 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/01 18:24:35 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	exit_error(char *message)
{
	ft_putstr_fd("\x1b[91m", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("\x1b[0m", 2);
	exit(1);
}

void	exit_usage(void)
{
	ft_printf("Usage: ./vm_champs/corewar [-dump N -s N -v N "
		"-nc] [-a] <[-n N] champion1.cor> <...>\n"
		"    -a        : Prints output from \"aff\" (Default is to hide it)\n"
		"#### TEXT OUTPUT MODE ################################################"
				"##########\n"
		"    -dump N      : Dumps memory after N cycles then exits\n"
		"    -s N      : Runs N cycles, dumps memory, pauses, then repeats\n"
		"    -v N      : Verbosity levels, can be added together to enable sev"
				"eral\n"
		"                - 0 : Show only essentials\n"
		"                - 1 : Show lives\n"
		"                - 2 : Show cycles\n"
		"                - 4 : Show operations (Params are NOT litteral ...)\n"
		"                - 8 : Show deaths\n"
		"                - 16 : Show PC movements (Except for jumps)\n"
		"#### NCURSES OUTPUT MODE ###########################################"
				"############\n"
		"    -nc       : Ncurses output mode\n"
		"###################################################################"
				"#############\n");
	exit(0);
}
