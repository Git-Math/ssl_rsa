/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:46:41 by mnguyen           #+#    #+#             */
/*   Updated: 2020/03/06 13:46:42 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

t_hash_table	*create_hash_table(t_uint32 size)
{
	t_hash_table	*hash_table;
	t_uint32		i;

	hash_table = (t_hash_table *)malloc(sizeof(t_hash_table));
	(hash_table == NULL) ? error(MALLOC_FAILED, "") : 0;
	hash_table->size = size;
	hash_table->node_array = (t_node **)malloc(sizeof(t_node *) * size);
	(hash_table->node_array == NULL) ? error(MALLOC_FAILED, "") : 0;
	i = 0;
	while (i < size)
	{
		hash_table->node_array[i] = NULL;
		i++;
	}
	return (hash_table);
}

void			free_hash_table(t_hash_table *hash_table)
{
	t_uint32	i;
	t_node		*current_node;
	t_node		*node_to_free;

	i = 0;
	while (i < hash_table->size)
	{
		current_node = hash_table->node_array[i];
		while (current_node)
		{
			node_to_free = current_node;
			current_node = current_node->next;
			free(node_to_free);
		}
		i++;
	}
	free(hash_table->node_array);
	free(hash_table);
}

t_uint32		calc_hash_index(t_hash_table *hash_table, t_uint64 key)
{
	return ((t_uint32)(key % (t_uint64)hash_table->size));
}

void			hash_insert(t_hash_table *hash_table, t_uint64 key, \
	t_uint32 val)
{
	t_uint32	hash_index;
	t_node		*new_node;

	hash_index = calc_hash_index(hash_table, key);
	new_node = (t_node *)malloc(sizeof(t_node));
	(new_node == NULL) ? error(MALLOC_FAILED, "") : 0;
	new_node->key = key;
	new_node->val = val;
	new_node->next = hash_table->node_array[hash_index];
	hash_table->node_array[hash_index] = new_node;
}

t_uint64		hash_search(t_hash_table *hash_table, t_uint64 key)
{
	int		hash_index;
	t_node	*node;
	t_node	*tmp;

	hash_index = calc_hash_index(hash_table, key);
	node = hash_table->node_array[hash_index];
	tmp = node;
	while (tmp)
	{
		if (tmp->key == key)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (0);
}
