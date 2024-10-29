/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:13:06 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/28 14:32:08 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ll_last(t_env *last)
{
	if (last == NULL)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

int	ft_lst_size(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ll_addback(t_env **env_head, t_env *new_node)
{
	t_env	*last

;	if (*env_head == NULL)
		return ;
	last = ll_last(*env_head);
	last->next = new_node;
}

//t_env	*ft_env_lstnew(char *key, char *value)
//{
//	t_env	*new_node;
	

//	new_node = ft_calloc(1, sizeof(t_env));
//	if (new_node == NULL)
//		return (NULL);
//	new_node->content = key_val_join(key, value);
//	if (new_node->content == NULL)
//		return (free_node(new_node), NULL);
//	new_node->name = ft_strdup(key);
//	if (new_node->name == NULL)
//		return (free_node(new_node), NULL);
//	new_node->value= ft_strdup(value);
//	if (new_node->value == NULL)
//		return (free_node(new_node), NULL);
//	new_node->next = NULL;
//	return (new_node);
//}
t_env	*ft_env_lstnew(char *key, char *value)
{
	t_env	*new_node;
	

	new_node = ft_calloc(1, sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->content = key_val_join(key, value);
	if (new_node->content == NULL)
		return (free_node(new_node), NULL);
	new_node->name = ft_strdup(key);
	if (new_node->name == NULL)
		return (free_node(new_node), NULL);
	new_node->value= ft_strdup(value);
	if (new_node->value == NULL)
		return (free_node(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}