/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleJoin.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:46:31 by harinrak          #+#    #+#             */
/*   Updated: 2026/03/01 08:46:34 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

void	Command::handleJoin(Client *client, const t_parse &parse){

    for (size_t i=0; i<parse.lst_param.size(); i++)
	{
        if(Utils::isValidChannel(parse.lst_param[i]) == false)
        {
            Logger::log(INFO, "invalid chanel by client");
			client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), ERR_NOSUCHCHANNEL, client->getNickName(), parse.lst_param[i], ERR_NOSUCHCHANNEL_MSG));
            continue;
        }
        if(this->_server.getChannelManager().channelExists(parse.lst_param[i])){
			Channel *channel = _server.getChannelManager().findChannel(parse.lst_param[i]);
            //Channel *channel=this->_server.getChannel(parse.lst_param[i]);
            if(channel->get_inv_only()==false && channel->isInThisChannel(client) == false)
			{
                client->joinChannel(channel);
                channel->add_client(client);
				std::string feadback = MessageBuilder::command(client->getNickName() + "!" + client->getUsrName() + "@" + client->getHname(), parse.command, parse.lst_param[i], "");
				//channel->send_to_member(client, feadback);
				_server.getChannelManager().broadcastToChannel(channel, feadback, client);
				client->catsendBuffer(feadback);
				Logger::log(INFO, "a client join channel " + parse.lst_param[i]);

			}
			else if (channel->get_inv_only()==true)
			{
				Logger::log(INFO, "a client try join channel a private Channel " + parse.lst_param[i]);
				client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), ERR_INVITEONLYCHAN, client->getNickName(), parse.lst_param[i], ERR_INVITEONLYCHAN_MSG));
            }
        }
        else{
			_server.getChannelManager().createChannel(parse.lst_param[i], client);
            //Channel *a=new Channel(parse.lst_param[i]);
            //this->_server.add_channel(a);
            //client->joinChannel(a);
            //a->add_client(client);
            //a->add_operator(client);
			client->catsendBuffer(MessageBuilder::command(client->getNickName() + "!" + client->getUsrName() + "@" + client->getHname(), parse.command, parse.lst_param[i], ""));
			Logger::log(INFO, "a client join a new channel " + parse.lst_param[i]);
        }
    }
}

