/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:56 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/08 14:44:47 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/get_next_line.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] < s2[i])
			return (-1);
		else if (s2[i] < s1[i])
			return (1);
		i++;
	}
	return (0);
}

void	get_from_here_doc(t_allvars *vars)
{
	char	*line;
	char	*lim;
	int		buff_size;

	line = 0;
	lim = ft_strjoin(vars->limiter, "", '\n');
	while (1)
	{
		line = get_next_line(0);
		buff_size = ft_strlen(line);
		if (ft_strcmp(line, lim) == 0)
		{
			free(line);
			break ;
		}
		write(vars->here_doc_pipe[0][1], line, buff_size);
		free(line);
	}
	free(lim);
	close(vars->here_doc_pipe[0][1]);
}
