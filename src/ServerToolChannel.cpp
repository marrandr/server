/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerToolChannel.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:27:07 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 08:30:13 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/Server.hpp"

//Channel* Server::getChannelByName(const std::string &channel)
//{
//	std::map<std::string, Channel*>::iterator it = _allChannelByName.find(channel);

//	if (it != _allChannelByName.end())
//		return (it->second);
//	else
//		return (NULL);
//}

//void Server::add_channel(Channel*ch){
//    this->_allChannelByName[ch->getName()]=ch;
//}

//Channel* Server::getChannel(const std::string&c_name){
//    std::map<std::string,Channel*>::iterator it=this->_allChannelByName.find(c_name);
//    return it->second;
//}

//bool Server::Channel_exists(const std::string&c_name)const{
//    std::map<std::string,Channel*>::const_iterator it=this->_allChannelByName.find(c_name);
//    if(it!=this->_allChannelByName.end())
//        return true;
//    return false;
//}
