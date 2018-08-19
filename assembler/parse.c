/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:08:29 by vchornyi          #+#    #+#             */
/*   Updated: 2018/04/20 17:08:30 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_next_argument(unsigned int *i, char *line)
{
	unsigned int	j;
	char			*arg;

	while (IS_WHITE_SPACE(line[*i]))
		(*i)++;
	j = 0;
	while (line[*i + j] && !IS_WHITE_SPACE(line[*i + j])
	&& line[*i + j] != SEPARATOR_CHAR && line[*i + j]
	!= COMMENT_CHAR && line[*i + j] != CMNT_CHAR)
		j++;
	if (j == 0)
		return (NULL);
	arg = ft_strsub(line, *i, j);
	if (!arg)
		exit(1);
	*i += j;
	return (arg);
}

static int	parse_operation(char *line, t_prog *prog)
{
	unsigned int	i;
	unsigned int	arg_i;
	t_op			*op;

	i = 0;
	op = init_op();
	while (!IS_WHITE_SPACE(line[i]) && line[i] != DIRECT_CHAR)
		i++;
	if (!(op->name = ft_strsub(line, 0, i)))
		exit(1);
	arg_i = 0;
	while (arg_i < 3)
	{
		while (IS_WHITE_SPACE(line[i]))
			i++;
		if (arg_i == 0)
			op->args[arg_i] = get_next_argument(&i, line);
		else if (line[i] && line[i] == SEPARATOR_CHAR && ++i)
			op->args[arg_i] = get_next_argument(&i, line);
		else if ((line[i] == COMMENT_CHAR) || (line[i] == CMNT_CHAR))
			break ;
		arg_i++;
	}
	convert_operations(op, prog);
	return (i);
}

static void	parse_line(char *line, t_prog *prog)
{
	int	i;
	int	label_size;

	i = 0;
	while (line[i])
	{
		if (IS_WHITE_SPACE(line[i]))
			i++;
		else if ((label_size = is_label(&line[i], prog)))
			i = label_size;
		else if ((line[i] == COMMENT_CHAR) || (line[i] == CMNT_CHAR))
			break ;
		else
		{
			i += parse_operation(&line[i], prog);
			while (IS_WHITE_SPACE(line[i]))
				i++;
			if (line[i] != COMMENT_CHAR && line[i] != CMNT_CHAR && line[i])
				error("Wrong chars after arguments");
			else
				break ;
		}
	}
}

static char	*get_pos(int key, t_file *file, int i, int what)
{
	if (key == NAME_CONTINUE || key == COMMENT_CONTINUE)
		return (&file->line[i]);
	if (what == NAME_START)
		return (&file->line[i + ft_strlen(NAME_CMD_STRING)]);
	else
		return (&file->line[i + ft_strlen(COMMENT_CMD_STRING)]);
}

void		parse_one_file(t_file *file, t_prog *prog, int *is_n, int *is_c)
{
	int	i;

	i = 0;
	while (IS_WHITE_SPACE(file->line[i]) && *is_n && *is_c != COMMENT_CONTINUE)
		i++;
	if ((!file->line[i] || file->line[i] == COMMENT_CHAR
		|| file->line[i] == CMNT_CHAR)
		&& *is_n != NAME_CONTINUE && *is_c != COMMENT_CONTINUE)
		;
	else if ((ft_strnstr(&file->line[i],
		NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))
		|| !*is_n) && *is_c != COMMENT_CONTINUE)
		*is_n = parse_name_comment(prog->header->prog_name,
			get_pos(*is_n, file, i, NAME_START), PROG_NAME_LENGTH, *is_n);
	else if ((ft_strnstr(&file->line[i],
		COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))
		|| *is_c == COMMENT_CONTINUE) && *is_n)
		*is_c = parse_name_comment(prog->header->comment,
			get_pos(*is_c, file, i, COMMENT_START), COMMENT_LENGTH, *is_c);
	else if (*is_n != NAME_END)
		error("No name");
	else if (*is_c != COMMENT_END)
		error("No comment");
	else
		parse_line(&file->line[i], prog);
}
