/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:55:17 by isemin            #+#    #+#             */
/*   Updated: 2024/07/02 10:56:34 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	new_n;
	int		size;
	char	*result;
	int		index;

	new_n = n;
	index = 0;
	if (n < 0)
	{
		new_n = (long)n * (-1);
		index = 1;
	}
	size = ft_num_digits(new_n) + index;
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	if (index == 1)
		result[0] = '-';
	while (index != size)
	{
		result[size-- - 1] = (new_n % 10) + '0';
		new_n = new_n / 10;
	}
	return (result);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		total;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s2 == NULL)
		return (s1);
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *) malloc(total * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	free(s2);
	return (str);
}
