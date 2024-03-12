/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:50:33 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/07 20:25:39 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	print_error(char *error_message, int place)
{
	if (place == 1)
		perror(error_message);
	else
		ft_putstr_fd(error_message, 2);
	exit(1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		write(fd, "(null)", 6);
		return ;
	}
	write(fd, s, ft_strlen(s));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	size_of_array(char	**array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
