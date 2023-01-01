/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:04:20 by abiru             #+#    #+#             */
/*   Updated: 2023/01/01 17:24:23 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*join_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

char	*get_line(char *tmp)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	if (*tmp == '\0')
		return (NULL);
	line = (char *)malloc(sizeof(char) * nl_pos(tmp) + 2);
	while (tmp[i] && tmp[i] != '\n')
	{
		line[i] = tmp[i];
		i++;
	}
	if (tmp[i] && tmp[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*read_line(int fd, char *fd_table)
{
	int		char_read;
	char	*nl;
	char	*buffer;

	char_read = 1;
	if (read(fd, 0, 0) == -1)
	{
		free(fd_table);
		return (NULL);
	}
	nl = ft_strchr(fd_table, '\n');
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!nl && char_read > 0)
	{
		char_read = read(fd, buffer, BUFFER_SIZE);
		buffer[char_read] = 0;
		fd_table = join_free(fd_table, buffer);
		nl = ft_strchr(buffer, '\n');
	}
	free(buffer);
	return (fd_table);
}

char	*get_next_line(int fd)
{
	static char	*fd_table[MAX_FD + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	if (!fd_table[fd])
		fd_table[fd] = ft_strdup("");
	fd_table[fd] = read_line(fd, fd_table[fd]);
	if (!fd_table[fd])
		return (NULL);
	line = get_line(fd_table[fd]);
	free(fd_table[fd]);
	fd_table[fd] = 0;
	return (line);
}

int	err_free_close(t_ints *t_int, t_strs *t_str)
{
	free_mem(t_str);
	free(t_int->pipes);
	free(t_str);
	close(t_int->infile);
	close(t_int->outfile);
	if (t_int->hd)
		unlink("heredoc");
	exit(1);
}
