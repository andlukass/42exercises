/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:11:56 by llopes-d          #+#    #+#             */
/*   Updated: 2023/04/30 18:49:22 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_get_length(long int i)
{
	int	length;

	length = 0;
	if (i == 0)
		return (1);
	if (i < 0)
	{
		i *= -1;
		length++;
	}
	while (i > 0)
	{
		i /= 10;
		length++;
	}
	return (length);
}
