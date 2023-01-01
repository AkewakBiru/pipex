/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 14:25:46 by abiru             #+#    #+#             */
/*   Updated: 2023/01/01 16:44:02 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_hd(t_strs *t_str, t_ints *t_int, int ac, char **av)
{
	char	**hd;

	hd = ft_split(av[1], ' ');
	if (ft_strncmp(hd[0], "here_doc", ft_strlen(av[1])) == 0)
	{
		t_int->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0000644);
		if (t_int->outfile < 0)
		{
			free_arr(hd);
			return (error_msg("file opening error\n", 0, 0));
		}
		t_int->hd = 1;
		t_str->lim = ft_strjoin(av[2], "\n");
	}
	free_arr(hd);
	return (t_int->hd);
}

int	here_doc(t_strs *t_str, t_ints *t_int)
{
	t_int->infile = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (t_int->infile < 0)
	{
		t_int->infile = t_int->pipes[1];
		return (error_msg("heredoc file opening error\n", 0, 0));
	}
	while (1)
	{
		write(1, "heredoc> ", 10);
		t_str->tmp = get_next_line(0);
		if (!t_str->tmp)
			err_free_close(t_int, t_str);
		if (ft_strncmp(t_str->tmp, t_str->lim, ft_strlen(t_str->tmp)) == 0)
		{
			free(t_str->tmp);
			break ;
		}
		write(t_int->infile, t_str->tmp, ft_strlen(t_str->tmp));
		free(t_str->tmp);
	}
	close(t_int->infile);
	t_int->infile = open("heredoc", O_RDONLY);
	if (t_int->infile < 0)
		return (error_msg("heredoc file opening error\n", 0, 0));
	return (0);
}

void	dup_close_bonus(t_ints t_int)
{
	if (t_int.counter == 0)
	{
		dup2(t_int.infile, STDIN_FILENO);
		dup2(t_int.pipes[1], STDOUT_FILENO);
	}
	else if (t_int.counter == t_int.cmds - 1)
	{
		dup2(t_int.pipes[2 * t_int.counter - 2], STDIN_FILENO);
		dup2(t_int.outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(t_int.pipes[2 * t_int.counter - 2], STDIN_FILENO);
		dup2(t_int.pipes[2 * t_int.counter + 1], STDOUT_FILENO);
	}
	close(t_int.infile);
	close(t_int.outfile);
	close_pipes(t_int);
}

void	close_pipes(t_ints t_int)
{
	int	i;

	i = -1;
	while (++i < (t_int.cmds - 1) * 2)
		close(t_int.pipes[i]);
}

int	check_init_file(char **s, t_ints *t_int, int ac, char **av)
{
	t_int->hd = 0;
	if (ft_strncmp(s[0], "here_doc", ft_strlen(s[0])) != 0)
	{
		t_int->infile = open(s[0], O_RDWR);
		if (t_int->infile < 0)
		{
			free_arr(s);
			return (write(2, av[1], ft_strlen(av[1])), perror(" "), 1);
		}
		t_int->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0000644);
		if (t_int->outfile < 0)
		{
			free_arr(s);
			return (error_msg("output file opening error\n", 0, 0));
		}
	}
	free_arr(s);
	return (0);
}
