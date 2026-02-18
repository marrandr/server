/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:09:14 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/17 18:09:15 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int ac, char *av[])
{
	if (ac != 3)
	{
		serverUsage(av[0]);
		return (1);
	}
	checkArgServer(av[0], av[1]);
	return (0);
}
