/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:04:09 by harinrak          #+#    #+#             */
/*   Updated: 2026/02/18 18:11:53 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd){
    this->fd=fd;
}
int Client::getFd()const{
    return fd;
}
const std::string& Client::getNickName()const{
    return _nick_name;
}
const std::string& Client::getUsrName()const{
    return _usr_name;
}
const StatusClient& Client::getState()const{
    return _state;
}
const std::string&Client::get_recBufer()const{
    return _recvBuffer;
}
const std::string&Client::get_sendBuffer()const{
    return _sendBuffer;
}
void Client::set_recvBuffer(const std::string& rcv){
    this->_recvBuffer=rcv;
}
void Client::set_sendBuffer(const std::string& send){
    _sendBuffer=send;
}
void Client::setState(StatusClient st){
    _state=st;
}
void Client::setNickName(const std::string& nick){
    this->_nick_name=nick;
}
void Client::setUsrName(const std::string& user){
    _usr_name=user;
}
//void Client::setState(StatusClient stat){
//    _state=stat;
//}
void Client::join(Channel*c){
    _channels.insert(c);
}
void Client::leave(Channel*c){
    _channels.erase(c);
}
const std::set<Channel*>& Client::getChannels()const{
    return _channels;
}
const std::string& Client::getRname()const{
    return _r_name;
}
void Client::setRname(const std::string& real){
    _r_name=real;
}

