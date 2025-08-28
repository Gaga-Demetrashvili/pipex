/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:13:44 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/28 19:36:01 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_model
{
	char	*infile_name;
	char	*outfile_name;
	char	**cmds_arr;
	char	***cmdv_arr;
	char	**envp;
	char	**paths;
	int		cmd_c;
}			t_model;

// validations
void		validations(int argc, char **argv, int pipe_res);

// validations_b
void		validations_b(int argc, char **argv);
int			ft_strcmp(const char *s1, const char *s2);

// utils
int			open_file(char *file_name, t_model model, int is_rdonly);
t_model		create_and_init_model(char **argv, int argc, char **envp);
void		execute_cmd(char **cmdv, char **envp, t_model model);

// cleanup
void		ft_error_exit(char *str, char *str2, t_model model, int status);
void		free_arr(char **arr);
void		clean_up_resources(t_model model);
int			is_empty_or_whitespace(char *str);

// find_path_utils
char		*find_path(char **cmdv, char **envp);
