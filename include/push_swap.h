/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 16:50:40 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/23 20:44:29 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct		s_pile
{
	struct s_pile	*next;
	struct s_pile	*last;
	int				n;
}					t_pile;

typedef struct		s_todo
{
	struct s_todo	*next;
	char			order;
}					t_todo;

enum { PA, PB, SA, SB, SS, RA, RB, RR, RRA, RRB, RRR };

int					apply(char *str, t_pile **p1, t_pile **p2);
int					main(int argc, char **argv);
int					parse(char *str, t_pile **p1, int *verbose);
void				doinstruct(char instruct, t_pile **p1, t_pile **p2);
void				printinstruct(void);
void				cleaninstruct(void);

#endif
