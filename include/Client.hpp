/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:39:23 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/12/25 16:26:01 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Client_HPP
#define Client_HPP

#include "Requests.hpp"
class Requests;

class   Client
{
    public:
    //add value bool to check response is send or not 
        bool isSend;
        Client();
        ~Client();
        Client(const Client &other);
        Client &operator=(const Client &other);
        Requests    *ClientRequest;
};

void PrintMap(std::__1::map<int, Client *> *_Map);

#endif