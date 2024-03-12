/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:53:16 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/08 15:53:38 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include <stdio.h>

# define ERROR_ARGC "Invalid count of arguments.\n"
# define ERROR_NOSF "No such file or directory.\n"
# define ERROR_PIPE "Pipeing failed\n"
# define ERROR_CMD "Command not found\n"
# define ERROR_MALLOC "Failed aloccating memory\n"
# define ERROR_FORK "Fork failed\n"
# define ERROR_DUP "Dup failed\n"

typedef struct s_allvars
{
	char	**paths;
	char	**cmd_and_flags;
	char	*cmd;
	char	*limiter;
	int		(*here_doc_pipe)[2];
	int		(*pipeing)[2];
	int		cmd_count;
	int		file1;
	int		file2;
	pid_t	id;
	int		is_here_doc;
}	t_allvars;

// Functions in utilities_1
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		print_error(char *error_message, int place);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

// Functions in utilities_2
char	**find_paths(char *envp[]);
void	args_files_validation(int argc, char *argv[], t_allvars *vars);
int		size_of_array(char	**array);
char	*cmd_exist(char **paths, char *cmd_name);

// Functions in utilities_3
void	close_pipes_files(t_allvars *vars);
void	running_cmds(char *argv[], char *envp[], t_allvars *vars);
void	init_vars(t_allvars *vars, char *envp[]);
void	pipeing_pipes(t_allvars *vars);
void	waiting_for_childs(void);

// Functions in utilities_4
void	get_from_here_doc(t_allvars *vars);

// Functions in ft_substr.c
char	*ft_substr(char const *s, unsigned int start, size_t len);

// Functions in ft_split.c
char	**ft_split(char const *s, char c);

// Functions in ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2, char sep);

// Functions in parent_child.c
void	first_cmd(char *argv[], char *envp[], t_allvars *vars, int i);
void	middle_cmd(char *argv[], char *envp[], t_allvars *vars, int i);
void	last_cmd(char *argv[], char *envp[], t_allvars *vars, int i);
void	free_split(char *array[]);

#endif