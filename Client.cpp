/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:04:09 by harinrak          #+#    #+#             */
/*   Updated: 2026/02/19 18:34:14 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd){
    this->fd=fd;
    _pass_word="";
    _state=NON_AUTH;
}
size_t Client::get_sizeAllchannel()const{
    return _channels.size();
}
void Client::leaveAllChannel(){
    _channels.clear();
}
bool Client::in_channel(Channel*ch)const{
    std::set<Channel*>::iterator it=_channels.find(ch);
    if(it!=_channels.end())
        return true;
    return false;
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
void Client::setState(StatusClient stat){
    _state=stat;
}
void Client::joinChannel(Channel*ch){
    if(ch){
        _channels.insert(ch);
    }
}
void Client::leaveChannel(Channel*ch){
    if(ch && this->in_channel(ch))
        _channels.erase(ch);
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
void Client::setPassword(const std::string& pass){
    _pass_word=pass;
}
void Client::catrecvBuffer(const std::string&to_cat){
    _recvBuffer=_recvBuffer+to_cat;
}
const std::string& Client::extractrcv_buffer()const{
    return (_recvBuffer+"\r\n");
}
bool Client::isAuthenticated() const{
    if(_state == AUTHENTICATED&&!_nick_name.empty()&&!_usr_name.empty() && !_pass_word.empty())
        return true;
    return false;
}
void Client::tryRegister() {
    if (_state == AUTHENTICATED&&!_nick_name.empty()&&!_usr_name.empty())
        _state = REGISTERED;
}

void	Client::trySendMessageOnBuffer()
{
	if (_sendBuffer.empty())
		return ;
	int	lenBuff = _sendBuffer.length();
	int	retSend = send(fd, (void *)&_sendBuffer, _sendBuffer.length(), MSG_NOSIGNAL);
	if (retSend == -1)
	{
		std::cerr << "[WARNING] : A client deconnect\n";
		close(fd);
	}
	else if (retSend < lenBuff)
		_sendBuffer = _sendBuffer.substr(lenBuff - retSend);
	else
		_sendBuffer.clear();
}

