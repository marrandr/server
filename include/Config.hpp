/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:17:52 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/27 15:31:00 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <sys/socket.h>
#define MAX_CLIENT SOMAXCONN
#define BUFFER_SIZE 1048576
#define	SERVER_VERSION "1.0"

class Config
{
	private:
		int	_port;
		std::string	_serverName;
		std::string	_pass;

	public:
		Config(int port, const std::string& ServerName, const std::string& pass);
		Config(const Config& copy);
		~Config();

		int getPort() const;
		int getMaxClients() const;
		const std::string &getServerName() const;
		const std::string &getPass() const;
};

#endif
