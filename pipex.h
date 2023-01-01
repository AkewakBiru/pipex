/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:11:18 by abiru             #+#    #+#             */
/*   Updated: 2023/01/01 16:36:48 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# define BUFFER_SIZE 42
# define MAX_FD 256

typedef struct fd_id {
	int		hd;
	int		cmds;
	int		*pipes;
	int		p_num;
	int		counter;
	int		infile;
	int		outfile;
}	t_ints;

typedef struct strs {
	char	*env_p;
	char	**ind_p;
	char	*lim;
	char	*tmp_cmd;
	char	**cmd_args;
	char	*tmp;
}	t_strs;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*get_envp(char **envp);
char	**sep_cmdopt(char *str);
char	*get_cmd_path(char **env, char *cmd);
void	free_arr(char **arr);
char	*ft_strdup(const char *s1);
void	free_mem(t_strs *str);
t_strs	*init_struct(void);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
int		nl_pos(char *str);
int		here_doc(t_strs *t_str, t_ints *t_int);
int		check_hd(t_strs *t_str, t_ints *t_int, int ac, char **av);
void	dup_close_bonus(t_ints t_int);
void	close_pipes(t_ints t_int);
int		err_free_close(t_ints *t_int, t_strs *t_str);
int		check_init_file(char **s, t_ints *t_int, int ac, char **av);
int		error_msg(char *msg, t_strs *t_str, int num);
#endif