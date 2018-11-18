/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 16:50:40 by ygaude            #+#    #+#             */
/*   Updated: 2018/11/18 18:14:13 by ygaude           ###   ########.fr       */
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
	struct s_todo	*prec;
	char			order;
	char			invert;
}					t_todo;

typedef struct		s_piles
{
	t_pile			**p1;
	t_pile			**p2;
}					t_piles;

enum { PA, PB, SA, SB, SS, RA, RB, RR, RRA, RRB, RRR };

int					apply(char *str, t_pile **p1, t_pile **p2);
int					parse(char *str, t_pile **p1, int *verbose);
void				doinstruct(char instruct, t_pile **p1, t_pile **p2);
void				printinstruct(void);
void				cleaninstruct(void);
void				quicksort(t_piles p, int until, int apile, int fiter);

t_todo				**getlist(void);
char				*strinstruct(char n);
void				addorder(t_todo **todo, char order);
void				delnext(t_todo *ptr);
int					isblocking(char order1, char order2);
int					isopposed(char order1, char order2);
int					ksorted(t_pile *pile, int apile);

int					del(t_todo **list);

void				smallsort(t_piles p);

int					visualize(t_piles p);

#endif
