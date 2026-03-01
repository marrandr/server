/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:22:23 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/27 11:40:14 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config(int port, const std::string& serverName, const std::string& pass) : _port(port), _serverName(serverName), _pass(pass)
{}

Config::Config(const Config& copy)
{
	if (this != &copy)
	{
		_port = copy.getPort();
		_pass = copy.getPass();
		_serverName = copy.getServerName();
	}
}
Config::~Config()
{}


int Config::getPort() const
{
	return (_port);
}


const std::string &Config::getServerName() const
{
	return (_serverName);
}

const std::string &Config::getPass() const
{
	return (_pass);
}


