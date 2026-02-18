/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:09:14 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/18 12:06:33 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int ac, char *av[])
{
	int	port = -1;

	if (ac != 3)
	{
		serverUsage(av[0]);
		return (1);
	}
	checkArgServer(av[0], av[1]);
	port = std::atoi(av[1]);
	try
	{
		Server	server(port);
		server.init();
		server.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return (0);
}
