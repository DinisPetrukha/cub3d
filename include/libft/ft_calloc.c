/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:31:09 by sephilip          #+#    #+#             */
/*   Updated: 2024/10/04 10:28:24 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

// what if (nmemb * size > 4294967295)
/*
int	main()
{
	char	*p;
	int	i;

	i = 0;
	p = (char *)(ft_calloc(5, sizeof(char)));
	while (i < 5)
	{
		p[i] = 'A';
		////printf"p: %c i: %d", p[i], i);
		i++;
	}
	//printf"%s\n", p);
	return (0);
}*/
