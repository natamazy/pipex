/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:53:16 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/08 16:15:35 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**find_paths(char *envp[])
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (paths == NULL)
				print_error(ERROR_MALLOC, 2);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

void	file_doc_validation(int argc, char *argv[], t_allvars *vars)
{
	vars->is_here_doc = 1;
	vars->cmd_count = argc - 4;
	vars->file1 = -1;
	vars->file2 = open(argv[argc - 1], O_CREAT | O_APPEND | O_RDWR, 0777);
	vars->pipeing = malloc(sizeof(int [2]) * vars->cmd_count - 1);
	if (!vars->pipeing)
		print_error(ERROR_MALLOC, 2);
	vars->here_doc_pipe = malloc(sizeof(int [2]) * 1);
	if (!vars->here_doc_pipe)
		print_error(ERROR_MALLOC, 2);
	pipe(vars->here_doc_pipe[0]);
	vars->limiter = argv[2];
	if (vars->limiter == NULL)
		print_error(ERROR_MALLOC, 2);
}

void	args_files_validation(int argc, char *argv[], t_allvars *vars)
{
	if (argc < 5)
		print_error(ERROR_ARGC, 2);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		file_doc_validation(argc, argv, vars);
	else
	{
		vars->cmd_count = argc - 3;
		vars->file1 = open(argv[1], O_RDONLY);
		if (vars->file1 < 0)
			print_error(argv[1], 1);
		vars->file2 = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
		vars->pipeing = malloc(sizeof(int [2]) * vars->cmd_count - 1);
		if (!vars->pipeing)
			print_error(ERROR_MALLOC, 2);
	}
}

char	*cmd_exist(char **paths, char *cmd_name)
{
	char	*final_path;
	int		i;

	i = 0;
	if (access(cmd_name, X_OK) == 0)
		return (cmd_name);
	while (paths[i])
	{
		final_path = ft_strjoin(paths[i], cmd_name, '/');
		if (access(final_path, X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}
