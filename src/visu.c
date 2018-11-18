/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 06:57:16 by ygaude            #+#    #+#             */
/*   Updated: 2018/11/18 18:30:44 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "push_swap.h"
#include "visu.h"

void			disp(t_piles p, t_winenv *env)
{
	if (!env->quit && SDL_GetTicks() >= env->visuticks + 1000 / 60)
	{
		displaystatus(p);
		env->visuticks = SDL_GetTicks();
	}
	while (!env->quit && env->autoplay &&
			SDL_GetTicks() < env->ticks + env->delay)
		;
	env->ticks = SDL_GetTicks();
}

t_todo			*getinput(void)
{
	t_todo	*todo;
	char	*str;
	int		i;

	todo = NULL;
	while (get_next_line(0, &str) > 0)
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		if (ft_strequ(str + i, "pa"))
			addorder(&todo, PA);
		else if (ft_strequ(str + i, "pb"))
			addorder(&todo, PB);
		else if (ft_strequ(str + i, "sa"))
			addorder(&todo, SA);
		else if (ft_strequ(str + i, "sb"))
			addorder(&todo, SB);
		else if (ft_strequ(str + i, "ss"))
			addorder(&todo, SS);
		else if (ft_strequ(str + i, "ra"))
			addorder(&todo, RA);
		else if (ft_strequ(str + i, "rb"))
			addorder(&todo, RB);
		else if (ft_strequ(str + i, "rr"))
			addorder(&todo, RR);
		else if (ft_strequ(str + i, "rra"))
			addorder(&todo, RRA);
		else if (ft_strequ(str + i, "rrb"))
			addorder(&todo, RRB);
		else if (ft_strequ(str + i, "rrr"))
			addorder(&todo, RRR);
		free(str);
	}
	addorder(&todo, -1);
	return (todo);
}

char		*vstrinstruct(char n)
{
	if (n == PA)
		return ("pa");
	else if (n == PB)
		return ("pb");
	else if (n == SA)
		return ("sa");
	else if (n == SB)
		return ("sb");
	else if (n == SS)
		return ("ss");
	else if (n == RA)
		return ("ra");
	else if (n == RB)
		return ("rb");
	else if (n == RR)
		return ("rr");
	else if (n == RRA)
		return ("rra");
	else if (n == RRB)
		return ("rrb");
	else if (n == RRR)
		return ("rrr");
	else
		return ("ERROR");
}

int				visualize(t_piles p)
{
	t_winenv		*env;
	t_todo			*todo;
	int				check;

	check = 1;
	todo = getinput();
	env = getsdlenv(*(p.p1));
	if (init())
		return (0);
	disp(p, env);
	while (check && todo && !env->quit)
	{
		if (events(env))
		{
			if (env->dir == 1 && todo->next)
			{
				check = apply(vstrinstruct(todo->order), p.p1, p.p2);
				todo = todo->next;
			}
			else if (env->dir == -1 && todo->prec)
			{
				todo = todo->prec;
				check = apply(vstrinstruct(todo->invert), p.p1, p.p2);
			}
		}
		disp(p, env);
	}
	while (events(env))
		displaystatus(p);
	SDL_Quit();

	t_todo	*tmp;
	while (todo->next)
	{
		check = apply(vstrinstruct(todo->order), p.p1, p.p2);
		todo = todo->next;
	}
	while (todo)
	{
		tmp = todo;
		todo = todo->prec;
		free(tmp);
	}
	return ((!check) ? -1 : (*p.p2 == NULL && issorted(*p.p1)));
}
