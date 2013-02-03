#include "Client_Server.hpp"

using namespace ColliderPlusPlus;

Client_Server::Client_Server()
{

  _name = "Default Client Server";
}

Client_Server::Client_Server(std::string name)
{
   _name = name;
}

Client_Server::~Client_Server()
{

}

OscMessenger& Client_Server::_getOscMessenger()
{
  return _oscm;
}

std::string Client_Server::_getName()
{
  return _name; 
}

bool Client_Server::pingScsynth()
{
  // finish me

  return false;
}
