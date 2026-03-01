/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:04:09 by harinrak          #+#    #+#             */
/*   Updated: 2026/02/28 21:00:49 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

Client::Client(int fd){
    this->fd=fd;
	_nick_name=DEFAUL_NICK;
    _pass_word="";
	_recvBuffer="";
	_sendBuffer="";
    _state=NON_AUTH;
	_welcome = false;
}

size_t Client::get_sizeAllchannel()const{
    return _channels.size();
}
void Client::leaveAllChannel(){
    std::set<Channel*>::iterator it=_channels.begin();
    while(it!=_channels.end()){
        it++;
    }
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
void Client::joinChannel(Channel*ch){
    if(ch){
        _channels.insert(ch);
    }
}
Client& Client::operator=(const Client&to_cpy){
    if(this!=&to_cpy){
        fd=to_cpy.fd;
        _pass_word=to_cpy._pass_word;
        _nick_name=to_cpy._nick_name;
        _usr_name=to_cpy._usr_name;
        _h_name=to_cpy._h_name;
        _s_name=to_cpy._s_name;
        _r_name=to_cpy._r_name;
        _state=to_cpy._state;
        _recvBuffer=to_cpy._recvBuffer;
        _sendBuffer=to_cpy._sendBuffer;
        _channels=to_cpy._channels;
        _welcome=to_cpy._welcome;
    }
    return *this;
}
Client::Client(const Client&to_cpy){
    *this=to_cpy;
}
void Client::leaveChannel(Channel*ch){
    if(ch && this->in_channel(ch)){
        _channels.erase(ch);
        ch->remove_client(this);
    }
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
void Client::catsendBuffer(const std::string&to_cat){
    _sendBuffer=_sendBuffer+to_cat;
}
bool Client::checkRecBuffer()const{
    size_t a=this->_recvBuffer.find(END);
    if(a!=std::string::npos)
        return true;
    return false;
}
bool Client::checkSendBuffer()const{
    size_t a=this->_sendBuffer.find(END);
    if(a!=std::string::npos)
        return true;
    return false;
}
std::string Client::getTrue_recvBuffer(){
    std::string to_ret="";
    if(this->checkRecBuffer()){
        std::string temp=this->get_recBufer();
        size_t a=this->_recvBuffer.find_last_of(END);
        to_ret=temp.substr(0,a);
        this->_recvBuffer=this->_recvBuffer.substr(a+1);
    }
    return to_ret;
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

bool Client::getWelcome() const
{
	return (_welcome);
}
const std::string&Client::getSname()const
{
	return (_s_name);
}
const std::string&Client::getHname()const
{
	return (_h_name);
}
void Client::setHname(const std::string& real)
{
	_h_name = real;
}
void Client::setSname(const std::string& real)
{
	_s_name = real;
}
void Client::setWelcome()
{
	_welcome = true;
}

