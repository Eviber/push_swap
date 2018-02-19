/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 06:57:16 by ygaude            #+#    #+#             */
/*   Updated: 2018/02/19 23:31:31 by ygaude           ###   ########.fr       */
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

int				visualize(t_piles p)
{
	t_winenv		*env;
	char			*str;
	int				i;
	int				check;

	check = 1;
	env = getsdlenv(*(p.p1));
	if (init())
		return (0);
	displaystatus(p);
	while (check && get_next_line(0, &str) > 0 && !(i = 0))
	{
		while (ft_isspace(str[i]))
			i++;
		check = apply(str + i, p.p1, p.p2);
		free(str);
		if (events(env))
			disp(p, env);
	}
	while (events(env))
		displaystatus(p);
	SDL_Quit();
	return ((!check) ? -1 : (*p.p2 == NULL && issorted(*p.p1)));
}
