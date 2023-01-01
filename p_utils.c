/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:12:49 by abiru             #+#    #+#             */
/*   Updated: 2023/01/01 16:37:26 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		s_len;
	int		ss_len;

	if (!s1)
		return (NULL);
	s_len = ft_strlen(s1);
	ss_len = ft_strlen(s2);
	ptr = malloc(sizeof(*s1) * (s_len + ss_len + 1));
	if (!ptr)
		return (NULL);
	s_len = 0;
	ss_len = 0;
	while (s1[s_len] != '\0')
	{
		ptr[s_len] = s1[s_len];
		s_len++;
	}
	while (s2[ss_len] != '\0')
		ptr[s_len++] = s2[ss_len++];
	ptr[s_len] = '\0';
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!dest)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_mem(t_strs *str)
{
	if (str->ind_p)
		free_arr(str->ind_p);
	if (str->env_p)
	{
		free(str->env_p);
		str->ind_p = NULL;
	}
	if (str->lim)
		free(str->lim);
	if (str->tmp_cmd)
		free(str->tmp_cmd);
	if (str->cmd_args)
		free_arr(str->cmd_args);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] > s2[i])
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		else if (s1[i] < s2[i])
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		i++;
	}
	return (0);
}
