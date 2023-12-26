#include "Config.hpp"
#include "Requests.hpp"




void sendResponseTest(std::string message , int sd)
{
	std::ostringstream	http_response;

	http_response << "HTTP/1.1 200 OK\r\n";
	http_response << "Content-Type: text/html\r\n";
	std::string	content("<html><body><h1>" + message + "</h1></body></html>");
	http_response << "Content-Length: " << content.size();
	http_response << "\r\n\r\n" << content;

	int ret = send(sd, http_response.str().c_str(), http_response.str().size(), 0);
	if (ret == -1) {
 		std::cout << "writing: client[" << sd <<"] disconnected" << std::endl;
		return;
	}
}

void Config::_sendResponse(int sd, std::map<int, Client *> ClientsInformation )
{

	Client *client = ClientsInformation[sd];
	std::cout << client->ClientRequest->GetMethod();
	std::cout << client->ClientRequest->GetRequestURI();
	std::vector<std::string> path;
	path.push_back("/");
	path.push_back("/test");

	if (client->ClientRequest->GetMethod() == "GET") // //****  check method if ** GET **    //*******
	{
		for (std::vector<std::string>::iterator it = path.begin(); it != path.end(); it++)
		{
			if (client->ClientRequest->GetRequestURI() == *it) // get resource type() 
			{
                // ---->>>>>>>>> check is file or directory <<<<<<-------
                // std::ifstream file("")
                std::cout << 
			 	std::cout << " =>>> " << client->ClientRequest->GetRequestURI()  << " "<< *it;
				sendResponseTest("<h1 style=\"color:green\">Found resource</h1>", sd);
			}
		}
		if(!client->isSend) // request resource not found in root
		{
			  sendResponseTest("<h1 style=\"color:red\">Not found 404</h1>", sd);
 		}
	}
    exit(0);
	// else if(client->ClientRequest->GetMethod() == "POST")// ****//  check method if ** POST **   //***** 
	// {

	// }
	// (void)ClientsInformation;
	// std::ostringstream	http_response;

	// http_response << "HTTP/1.1 200 OK\r\n";
	// http_response << "Content-Type: text/html\r\n";
	// std::string	content("<html><body><h1>Hello, this is a simple HTTP response!</h1></body></html>");
	// http_response << "Content-Length: " << content.size();
	// http_response << "\r\n\r\n" << content;

	// int ret = send(sd, http_response.str().c_str(), http_response.str().size(), 0);
	// if (ret == -1) {
	// 	_rmPollfd(sd);
	// 	std::cout << "writing: client[" << sd <<"] disconnected" << std::endl;
	// 	return;
	// }
}