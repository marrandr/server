/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 07:39:25 by harinrak          #+#    #+#             */
/*   Updated: 2026/03/01 09:07:54 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string& name){
    this->_name=name;
    _invite_only=false;
    user_limits=-1;
    _topics="";
    _pass=false;
    _pass_word="";
    _only_ops=false;
}
const std::string& Channel::getName(){
    return _name;
}

Channel& Channel::operator=(const Channel& to_cpy){
    if(this!=&to_cpy){
        _name=to_cpy._name;
        _topics=to_cpy._topics;
        user_limits=to_cpy.user_limits;
        _invite_only=to_cpy._invite_only;
        _clients=to_cpy._clients;
        _ops=to_cpy._ops;
        _pass=to_cpy._pass;
        _pass_word=to_cpy._pass_word;
        _only_ops=to_cpy._only_ops;
    }
    return *this;
}

size_t	Channel::getNbUserChannel() const
{
	return (_clients.size());
}


Channel::Channel(Channel* to_cpy){
    *this=to_cpy;
}
void Channel::add_client(Client*to_add){
    if(user_limits<0 || (size_t)user_limits>_clients.size())
        _clients.insert(to_add);
}
//void Channel::set_usr_limits(int limits){
//    if(limits>0)
//        user_limits=limits;
//}
void Channel::remove_client(Client*to_remove){
    if(this->is_operator(to_remove))
        this->remove_ops(to_remove);
    _clients.erase(to_remove);
}
bool Channel::get_inv_only()const{
    return _invite_only;
}
// void Channel::set_invite(bool inv){
//     _invite_only=inv;
// }
void Channel::add_operator(Client*ops){
    if((size_t)user_limits>_ops.size())
        _ops.insert(ops);
}
int Channel::get_user_limits()const{
    return user_limits;
}
bool Channel::is_operator(Client*ops){
    std::set<Client*>::iterator a=this->_ops.find(ops) ;
    if(a!=_ops.end())
        return true;
    return false;
}
void Channel::remove_ops(Client*cl){
    if(this->is_operator(cl)){
        _ops.erase(cl);
    }
}
const std::set<Client*> Channel::getClients()const{
    return _clients;
}
Channel::~Channel(){
    _clients.clear();
    _ops.clear();
}

