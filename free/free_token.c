/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btekinli <btekinli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:47:57 by btekinli          #+#    #+#             */
/*   Updated: 2022/10/13 01:03:20 by btekinli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(void)
{
	t_token		*tmp;
	t_token		*token;

	token = g_ms.token;
	while (token)
	{
		free(token->str);
		token = token->next;
	}
	token = g_ms.token;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}
