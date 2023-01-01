/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:41:42 by abiru             #+#    #+#             */
/*   Updated: 2023/01/01 16:44:14 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_msg(char *msg, t_strs *t_str, int num)
{
	write(2, msg, ft_strlen(msg));
	if (num == 0)
		return (1);
	write(2, ": ", 2);
	if (num == 1)
		write(2, t_str->tmp_cmd, ft_strlen(t_str->tmp_cmd));
	return (write(2, "\n", 1));
}

void	ex_fail_msg(t_strs	*t_str)
{
	if (ft_strchr(t_str -> cmd_args[0], '/')
		&& access(t_str -> cmd_args[0], F_OK) != 0)
		error_msg("No such file or directory", t_str, 1);
	else
		error_msg("command not found", t_str, 1);
}

void	exec_cmd(char **av, t_ints t_int, t_strs *t_str)
{
	t_int.p_num = fork();
	if (t_int.p_num == 0)
	{
		t_str->cmd_args = ft_split(av[t_int.counter + 2 + t_int.hd], ' ');
		if (t_str->cmd_args[0] == 0)
			t_str->tmp_cmd = ft_strdup("");
		else if ((ft_strchr(t_str->cmd_args[0], '/'))
			|| (t_str->cmd_args[0] && !t_str->env_p))
			t_str->tmp_cmd = ft_strdup(t_str->cmd_args[0]);
		else if (t_str->env_p)
			t_str->tmp_cmd = get_cmd_path(t_str->ind_p, t_str->cmd_args[0]);
		dup_close_bonus(t_int);
		execve(t_str->tmp_cmd, t_str->cmd_args, NULL);
		ex_fail_msg(t_str);
		free_mem(t_str);
		free(t_str);
		free(t_int.pipes);
		exit (1);
	}
}

int	pipex(char **av, t_ints t_int, t_strs *t_str)
{
	t_int.pipes = (int *)malloc(sizeof(int) * (t_int.cmds - 1) * 2);
	if (!t_int.pipes)
		return (0);
	t_int.counter = -1;
	while (++t_int.counter < t_int.cmds - 1)
	{
		if (pipe(t_int.pipes + 2 * t_int.counter) < 0)
			return (error_msg("Pipe creation error\n", 0, 0));
	}
	if (t_int.hd == 1)
		here_doc(t_str, &t_int);
	t_int.counter = -1;
	while (++t_int.counter < t_int.cmds)
		exec_cmd(av, t_int, t_str);
	close_pipes(t_int);
	close(t_int.infile);
	close(t_int.outfile);
	free_mem(t_str);
	t_int.counter = -1;
	while (++t_int.counter < t_int.cmds)
		waitpid(-1, NULL, 0);
	return (free(t_str), free(t_int.pipes), 0);
}

int	main(int ac, char **av, char **envp)
{
	t_ints	t_int;
	t_strs	*t_str;
	char	**s;

	if (ac < 5)
		return (error_msg("You need 4 arguments\n", 0, 0));
	s = ft_split(av[1], ' ');
	if (ac < 5 || (!ft_strncmp(s[0], "here_doc", ft_strlen(s[0])) && ac < 6))
	{
		free_arr(s);
		return (error_msg("Not enough arguments\n", 0, 0));
	}
	if (check_init_file(s, &t_int, ac, av) == 1)
		return (1);
	t_str = init_struct();
	t_str->env_p = get_envp(envp);
	t_str->ind_p = ft_split(t_str->env_p, ':');
	t_int.hd = check_hd(t_str, &t_int, ac, av);
	t_int.cmds = ac - 3 - t_int.hd;
	pipex(av, t_int, t_str);
	if (t_int.hd)
		unlink("heredoc");
	return (0);
}
