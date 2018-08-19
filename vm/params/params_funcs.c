/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:17:46 by omykolai          #+#    #+#             */
/*   Updated: 2018/05/03 15:34:16 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int			get_int(const char *str)
{
	int i;

	i = 0;
	if (str[i] == '+')
		++i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			exit_error("numeric parameters must be non negative "
						"integer numbers");
		i++;
	}
	i = ft_atoi(str);
	if (ft_strlen(str) > 10 || i > 2000000000)
		exit_error("big numbers are evil");
	return (ft_atoi(str));
}

int			get_player_num(t_params *p, int n, bool check_custom)
{
	bool	has_num;
	int		j;

	has_num = true;
	while (has_num)
	{
		j = -1;
		has_num = false;
		while (++j < p->i)
			if ((!check_custom || p->champ_custom_num[j])
				&& p->champ_nums[j] == n)
				has_num = true;
		if (has_num)
		{
			if (check_custom)
				exit_error("players can't have same numbers");
			--n;
		}
	}
	return (n);
}

void		set_player_num(t_params *p, int i)
{
	int		n;

	if (p->champ_custom_num[i])
		return ;
	n = -1;
	p->champ_nums[i] = get_player_num(p, n, false);
}

void		define_player(t_params *p, int argc, char **argv, int i)
{
	if (i == argc)
		exit_usage();
	p->champ_names[p->i] = argv[i];
	++p->i;
}

int			set_custom_player(t_params *p, int argc, char *argv[], int i)
{
	int		n;

	if (i == argc - 1)
		exit_usage();
	n = get_int(argv[++i]);
	if (n == 0)
		exit_error("player number can't be zero");
	p->champ_custom_num[p->i] = 1;
	define_player(p, argc, argv, ++i);
	--p->i;
	p->champ_nums[p->i] = get_player_num(p, -n, true);
	++p->i;
	return (i);
}
