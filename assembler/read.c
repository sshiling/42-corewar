/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:40:23 by vchornyi          #+#    #+#             */
/*   Updated: 2018/04/20 15:40:24 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		error(char *error_message)
{
	ft_putendl_fd(error_message, 2);
	exit(1);
}

static void	add_line_to_file(t_file **file, char *line)
{
	t_file *iter;

	if (!*file)
		*file = init_file(line);
	else
	{
		iter = *file;
		while (iter->next)
			iter = iter->next;
		iter->next = init_file(line);
	}
}

static void	check_last_new_line(char *file_name)
{
	int		fd;
	char	*file;
	char	*last_n;
	int		i;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		error("Can't read source file");
	file = ft_readfile(fd, 200);
	if (!file)
		return ;
	last_n = ft_strrchr(file, '\n');
	i = 0;
	while (last_n && last_n[i] && (IS_WHITE_SPACE(last_n[i])
	|| last_n[i] == COMMENT_CHAR || last_n[i] == CMNT_CHAR))
		i++;
	if (last_n && last_n[i])
		error("No new line");
	close(fd);
	ft_strdel(&file);
}

void		read_file(t_prog *prog, char *file_name)
{
	int		fd;
	char	*line;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		error("Can't read source file");
	prog->file_name = file_name;
	while (get_next_line(fd, &line) > 0)
		add_line_to_file(&prog->file, line);
	close(fd);
	check_last_new_line(file_name);
}
