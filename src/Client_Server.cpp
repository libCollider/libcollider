#include "Client_Server.hpp"
#include <iostream>

using namespace ColliderPlusPlus;

Client_Server::Client_Server()
:_nextNode(1000), _name("Default Server")
{

 // _name = "Default Client Server" ;
 // _nextNode = 1000;
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

int Client_Server::_nextNodeID()
{
  //unique node ids start at 1000 and go up from there
  _nodeIDs.push_back(_nextNode);
  _nextNode++;
  return _nextNode;
}

void Client_Server::_printNodes()
{
  std::vector<int>::iterator iter = _nodeIDs.begin();
  for(; iter != _nodeIDs.end();iter++)
  {
    std::cout << "Node id: " << *iter << std::endl;
  } 
}

void Client_Server::_queryNodeTree()
{
 // std::cout << Node

}

bool Client_Server::_pingScsynth()
{
  // finish me

  return false;
}
