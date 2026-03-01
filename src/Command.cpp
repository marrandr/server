/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 06:17:41 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/28 20:42:06 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"
#include "../include/parse.hpp"

Command::Command(Server &server) : _server(server)
{}

void	Command::execute(Client *client, const t_parse &parse)
{
	int	index = -1;
	std::string allCmd[11] = {"PASS", "CAP", "USER", "NICK", "PRIVMSG", "JOIN", "MODE", "PING", "PONG" , "QUIT", "EXIT"};
	//void (Command::*cmd[9])(Client*, const t_parse &) = {&Command::handlePass, &Command::handleCap, &Command::handleUser, &Command::handleNick, &Command::handlePrivmsg, &Command::handleJoin, &Command::handlePing, &Command::handlePong, &Command::handleQuit, &Command::handleExit};
	void (Command::*cmd[11])(Client*, const t_parse &) = {&Command::handlePass, &Command::handleCap, &Command::handleUser, &Command::handleNick, &Command::handlePrivmsg, &Command::handleJoin};

	for (int i = 0; i < 6; i++)
		if (parse.command == allCmd[i])
		{
			index = i;
			break ;
		}
	if (index != -1)
	{
		if (index > 2 && client->getState() == NON_AUTH)
		{
			client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), ERR_NOTREGISTERED, client->getNickName(), parse.command, ERR_NOTREGISTERED_MSG));
			Logger::log(INFO, "Error cmd : " + parse.command );
		}
		else
			(this->*cmd[index])(client, parse);
	}
}

void	Command::handleDataReceve(Client *client)
{
	if (client->checkRecBuffer())
	{
		std::vector<t_parse>	pars = parser::finalizeParse(client->getTrue_recvBuffer());
		for (unsigned int i = 0; i < pars.size(); i++)
		{
			if (!pars[i].error_code.empty())
			{
				client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), pars[i].error_code, client->getNickName(), pars[i].command, pars[i].error_msg));
				Logger::log(INFO, "Error cmd : " + pars[i].command);
				continue ;
			}
			execute(client, pars[i]);
		}
	}
}

