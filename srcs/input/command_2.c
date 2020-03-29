/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:31:02 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/29 12:10:04 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The t_cmd structure is a dynamic array, including a 'char * raw' that wrap
// the command itself, a 'size_t len' that contains the cmd length,
// a 'size_t capacity' that indicates how many bytes have been allocated,
// that is also the max length cmd can be and a 'size_t pos' showing us
// the cursor position is the raw, vefry useful for command editing.

// Return an initialized command struct
t_cmd	*cmd_new()
{
	t_cmd *cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	if (!(cmd->raw = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	ft_memset(cmd->raw, 0, BUFFER_SIZE + 1);
	cmd->capacity = BUFFER_SIZE;
	cmd->len = 0;
	cmd->pos = 0;
	return (cmd);
}

// Realloc the command struct with two times more space
t_bool	cmd_stretch(t_cmd *cmd)
{
	char	*new_raw;

	if (!cmd)
		return (failure);
	cmd->capacity *= 2;
	if (!(new_raw = malloc(sizeof(char) * (cmd->capacity + 1))))
		return (failure);
	ft_memset(new_raw, 0, cmd->capacity + 1);
	ft_memcpy(new_raw, cmd->raw, cmd->len);
	if (cmd->raw)
		free(cmd->raw);
	cmd->raw = new_raw;
	return (success);
}

// Delete the command's content, without freeing it as we can reuse it later
void	cmd_erase(t_cmd *cmd)
{
	if (cmd && cmd->raw)
	{
		ft_memset(cmd->raw, 0, cmd->capacity);
		cmd->len = 0;
		cmd->pos = 0;
	}
}

// Free the command
void	cmd_free(t_cmd *cmd)
{
	if (cmd && cmd->raw)
		free(cmd->raw);
	if (cmd)
		free(cmd);
}
