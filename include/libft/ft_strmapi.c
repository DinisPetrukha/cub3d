/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:13:00 by sephilip          #+#    #+#             */
/*   Updated: 2024/09/29 13:18:38 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char	test(unsigned int i, char b)
{
	b = b - 32;
	return (b);
}*/
//T:DO TEST WITHOUT TEMP S FOR THE CHAR CONST

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*p;
	char	*ret;

	i = 0;
	p = (char *)s;
	len = ft_strlen(p);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = (*f)(i, p[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}
/*
int	main()
{
	//printf"%s\n", ft_strmapi("abcdef", &test));
	return (0);
}*/
