/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshiling <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 16:38:14 by sshiling          #+#    #+#             */
/*   Updated: 2018/04/20 16:38:16 by sshiling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	check_max_len(int len, int max_len, int key)
{
	if (len > max_len && (key == NAME_CONTINUE || key == NAME_START))
		error("too long name");
	else if (len > max_len && (key == COMMENT_CONTINUE || key == COMMENT_START))
		error("too long comment");
}

static void	add_to_string(char *to, char *from, int is_delete)
{
	int		i;

	i = 0;
	while (to[i])
		i++;
	ft_strncpy(&to[i], from, ft_strlen(from));
	if (is_delete)
		ft_strdel(&from);
}

static void	check_line_ending(char *line, int key)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(IS_WHITE_SPACE(line[i]) && line[i]
			!= COMMENT_CHAR && line[i] != CMNT_CHAR)
			&& (key == NAME_CONTINUE || key == NAME_START))
			error("Bad characters in the end of name");
		else if (!(IS_WHITE_SPACE(line[i]) && line[i]
			!= COMMENT_CHAR && line[i] != CMNT_CHAR)
			&& (key == COMMENT_CONTINUE || key == COMMENT_START))
			error("Bad characters in the end of comment");
		i++;
	}
}

static int	check_line(char *from, int key)
{
	int		i;

	i = 0;
	while (IS_WHITE_SPACE(from[i]))
		i++;
	if (key == NAME_END || key == COMMENT_END)
		error(key == NAME_END ? "Duplicate name" : "Duplicate comment");
	if ((key == NAME_START || key == COMMENT_START) && from[i] != '\"')
		error(key == NAME_START ?
			"Bad characters at the start of name or no name found" :
			"Bad characters at the start of comment or no comment found");
	return ((key == NAME_CONTINUE || key == COMMENT_CONTINUE) ? 0 : i + 1);
}

int			parse_name_comment(char *to, char *from, int max_len, int key)
{
	char	*last_char;
	char	*current;
	int		i;

	i = check_line(from, key);
	if (!(last_char = ft_strchr(&from[i], '\"')))
	{
		check_max_len(ft_strlen(to) + ft_strlen(&from[i]), max_len, key);
		add_to_string(to, &from[i], 0);
		add_to_string(to, "\n", 0);
		return ((key == NAME_CONTINUE || key == NAME_START) ?
			NAME_CONTINUE : COMMENT_CONTINUE);
	}
	if (!(current = ft_strnew(last_char - &from[i])))
		exit(1);
	current = ft_strncpy(current, &from[i], last_char - &from[i]);
	check_max_len(ft_strlen(to) + ft_strlen(current), max_len, key);
	add_to_string(to, current, 1);
	check_line_ending(&last_char[1], key);
	return ((key == NAME_CONTINUE
		|| key == NAME_START) ? NAME_END : COMMENT_END);
}
