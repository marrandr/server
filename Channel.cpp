/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harinrak <harinrak@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 07:39:25 by harinrak          #+#    #+#             */
/*   Updated: 2026/02/19 11:32:13 by harinrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel(const std::string& name){
    this->_name=name;
    _invite_only=false;
    user_limits=2;
}
void Channel::add_client(Client*to_add){
    if(to_add && user_limits<_clients.size())
        _clients.insert(to_add);
}
void Channel::set_usr_limits(size_t limits){
    if(limits>0)
        user_limits=limits;
}
void Channel::remove_client(Client*to_remove){
    if(to_remove){
        if(this->is_operator(to_remove))
            this->remove_ops(to_remove);
        _clients.erase(to_remove);
    }
}
void Channel::set_invite(bool inv){
    _invite_only=inv;
}
void Channel::add_operator(Client*ops){
    if(ops && user_limits<_ops.size())
        _ops.insert(ops);
}
size_t Channel::get_user_limits()const{
    return user_limits;
}
bool Channel::is_operator(Client*ops)const{
    if(ops){
        const std::set<Client*>::const_iterator a=this->_ops.find(ops);
        if(a!=_ops.end())
            return true;
        return false; 
    }
    return false;
}
void Channel::remove_ops(Client*cl){
    if(this->is_operator(cl)){
        _ops.erase(cl);
    }
}
const std::set<Client*>& Channel::getClient()const{
    return _clients;
}
Channel::~Channel(){
    _clients.clear();
    _ops.clear();
}