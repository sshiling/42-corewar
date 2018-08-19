/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:17:24 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/02 16:29:36 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		set_mode_arg(t_params *p, int argc, char **argv, int *i)
{
	if (*i == argc - 1)
		exit_usage();
	if (p->mode == V_MODE)
		p->arg.v = get_int(argv[++*i]);
	else
		p->arg.n = get_int(argv[++*i]);
}

int				define_mode(t_params *p, int argc, char **argv, int i)
{
	static const char	*flag[NB_OF_FLAGS] = {"-nc", "-dump", "-v", "-s", "-a"};
	int					j;

	j = -1;
	while (++j < NB_OF_FLAGS)
	{
		if (ft_strequ(argv[i], flag[j]))
		{
			if (j == A_MODE)
				p->aff_works = true;
			else
			{
				if (p->mode != BASIC_MODE)
					exit_usage();
				p->mode = j;
				if (p->mode != NCURSES_MODE)
					set_mode_arg(p, argc, argv, &i);
			}
			return (i);
		}
	}
	exit_usage();
	return (-1);
}

void			set_params(t_params *p, int argc, char *argv[])
{
	int			i;

	i = 0;
	while (++i < argc)
	{
		if (*argv[i] == '-')
		{
			if (ft_strequ(argv[i], "-n"))
				i = set_custom_player(p, argc, argv, i);
			else
				i = define_mode(p, argc, argv, i);
		}
		else
			define_player(p, argc, argv, i);
	}
	i = -1;
	while (++i < p->i)
		set_player_num(p, i);
}

void			init_params(t_params *p)
{
	int i;

	p->i = 0;
	p->mode = BASIC_MODE;
	p->arg.n = 0;
	p->arg.v = 0;
	p->aff_works = false;
	p->step_by_step_mode = true;
	i = -1;
	while (++i < MAX_PLAYERS)
		p->champ_custom_num[i] = 0;
}
