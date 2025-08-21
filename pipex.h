/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:13:44 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/21 22:01:28 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

// Pipex utils
int	open_file(char *file_name, int is_rdonly);
int	validations(int argc, int pipe_res);