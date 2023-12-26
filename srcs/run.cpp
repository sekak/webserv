#include "Config.hpp"
#include "Requests.hpp"

void Config::_readRequest(int sd)
{

	// The server-name WILL be checked after reading the request

	char buffer[BUFFER_SIZE];
	int ret;

	memset(buffer, 0, BUFFER_SIZE);
	ret = recv(sd, buffer, BUFFER_SIZE - 1, 0);

	if (!ret || ret == -1)
	{
		_rmPollfd(sd);
		std::cout << "reading: client[" << sd << "] disconnected" << std::endl;
		return;
	}
	_readStr += buffer;
}


void Config::run()
{
	Printers::print_serversSockets(_portToServersSocket);

	ServersSocket *sS;
	std::map<int, Client *> ClientsInformation;

	while (!g_sigint)
	{
		Client *_Client = new Client();
		if ((poll(_pollFds.data(), _pollFds.size(), -1)) <= 0)
			continue;
		for (size_t i = 0; i < _pollFds.size(); i++)
		{
			int sd = _pollFds[i].fd;
			if ((_pollFds[i].revents & POLLERR) || _pollFds[i].revents & POLLHUP)
			{
				if ((sS = _sdToServersSocket[sd]) && sS->getFd() == sd)
					_unplugSocket(sS);
				_rmPollfd(sd);
				std::cerr << "POLL QUIT " << sd << std::endl;
			}
			else if (_pollFds[i].revents & POLLIN)
			{
				if ((sS = _sdToServersSocket[sd]) && sS->getFd() == sd)
				{
					sockaddr_in client_addr;
					socklen_t client_addr_len = sizeof(client_addr);
					int client_fd = accept(sd, (struct sockaddr *)&client_addr, &client_addr_len);
					if (client_fd < 0)
						continue;
					_sdToServersSocket[client_fd] = sS;
					_addPollfd(client_fd, POLLIN | POLLOUT);
				}
				else // read request from client
				{
					_readRequest(sd);
					HandleRequest(_readStr, sd, &ClientsInformation, _Client);
					_readStr = "";
				}
			}
			else if (_pollFds[i].revents & POLLOUT) // send response to the client
			{
				_sendResponse(sd, ClientsInformation);
			}
		}
	}
}