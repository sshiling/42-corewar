/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:25:53 by vchornyi          #+#    #+#             */
/*   Updated: 2018/04/24 13:25:54 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label			*add_label(t_label **label, char *name,
							unsigned int addr, int size)
{
	t_label		*iter;

	if (!*label)
	{
		*label = init_label(name, addr, size);
		return (*label);
	}
	else
	{
		iter = *label;
		while (iter->next)
			iter = iter->next;
		iter->next = init_label(name, addr, size);
		return (iter->next);
	}
}

static t_label	*find_label_by_name(t_label *labels_list, char *name)
{
	t_label	*iter;

	iter = labels_list;
	while (iter)
	{
		if (ft_strequ(iter->name, name))
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

int				is_label(char *line, t_prog *prog)
{
	int		i;
	char	*name;

	i = 0;
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		i++;
	if (line[i] == LABEL_CHAR)
	{
		name = ft_strsub(line, 0, (size_t)i);
		if (!name)
			exit(1);
		add_label(&prog->labels, name, prog->idx, 4);
		return (++i);
	}
	return (0);
}

static void		replace_bytes(t_prog *prog, unsigned int idx,
								int value, int num_bytes)
{
	unsigned int	*p4;
	unsigned short	*p2;

	if (num_bytes == 4)
	{
		p4 = (unsigned int *)&prog->prog[idx];
		*p4 = reverse_bytes(value, 4);
	}
	else if (num_bytes == 2)
	{
		p2 = (unsigned short *)&prog->prog[idx];
		*p2 = (unsigned short)reverse_bytes(value, 2);
	}
}

void			fill_empty_labels(t_prog *prog)
{
	t_label *iter;
	t_label	*label;

	iter = prog->empty_labels;
	while (iter)
	{
		label = find_label_by_name(prog->labels, iter->name);
		if (!label)
			error("No such label while attempting to dereference");
		replace_bytes(prog, iter->addr, label->addr - iter->val, iter->size);
		iter = iter->next;
	}
}
