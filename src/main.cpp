/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:09:14 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/27 11:10:43 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/handleSignal.hpp"

sig_atomic_t gRun = 1;

int main(int ac, char *av[])
{
	signal(SIGQUIT, handleSignal);
	signal(SIGTERM, handleSignal);
	signal(SIGINT, handleSignal);
	int	port = -1;

	if (ac != 3)
	{
		serverUsage(av[0]);
		return (1);
	}
	checkArgServer(av[0], av[1], av[2]);
	port = std::atoi(av[1]);
	try
	{
		Config	config(port, av[0], av[2]);
		Server	server(config);
		server.init();
		server.run();
		server.stop();
	}
	catch(const std::exception& e)
	{
		Logger::log(ERROR, e.what());
	}

	return (0);
}
