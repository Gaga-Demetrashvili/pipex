/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:03:55 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/10 19:03:55 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*memory_block;

	total_size = nmemb * size;
	memory_block = malloc(total_size);
	if (memory_block == NULL)
		return (NULL);
	ft_memset(memory_block, '\0', total_size);
	return (memory_block);
}

// int	main(void)
// {
// 	size_t nmemb = 7;

// 	void *allocated_memory = ft_calloc(nmemb, 1);
// 	void *fill_memory = ft_memset(allocated_memory, 'A', nmemb);
// 	free(fill_memory);

// 	return (0);
// }