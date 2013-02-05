#include "Client_Server.hpp"
#include <iostream>

using namespace ColliderPlusPlus;

Client_Server::Client_Server()
:_nextNode(1000), _name("Default Server")
{
  _setHost("127.0.0.1");
  _setPort("57110");
}

Client_Server::Client_Server(std::string name)
:_nextNode(1000), _name(name)
{
  _setHost("127.0.0.1");
  _setPort("57110");
}

Client_Server::Client_Server(const std::string name, const char *host, const char *port)
:_nextNode(1000), _name(name)
{
  _setHost(host);
  _setPort(port);
}

Client_Server::~Client_Server()
{

}

OscMessenger& Client_Server::_getOscMessenger()
{
  return _oscm;
}

void Client_Server::_dumpOSC(int toggle)
{
  _oscm._dumpOSC(toggle);
}


std::string Client_Server::_getName()
{
  return _name; 
}

int Client_Server::_nextNodeID()
{
  //unique node ids start at 1000 and go up from there
  int firstNodeId = _pushFirstNodeId(_nextNode);
  _nextNode++;
    

  return firstNodeId;
}

int Client_Server::_pushFirstNodeId(int nextNode)
{
  _nodeIDs.push_back(nextNode);
  return nextNode;
}

void Client_Server::_printCurrentNodeIds()
{
  std::vector<int>::iterator iter = _nodeIDs.begin();
  for(; iter != _nodeIDs.end();iter++)
  {
    std::cout << "Node id: " << *iter << std::endl;
  } 
}

void Client_Server::_queryNodeTree()
{
  _oscm._queryNodeTree();
} 

void Client_Server::_createNode(std::string name, int nodeID, int pauseTime)
{
  _oscm._createNode(name, nodeID, pauseTime);
}

void Client_Server::_freeNode(int nodeID, int pauseTime)
{
  _oscm._freeNode(nodeID,pauseTime);
}

void Client_Server::_killServer(int pauseTime)
{
  _oscm._killServer(pauseTime);
}

bool Client_Server::_pingScsynth()
{
  // finish me

  return false;
}

void Client_Server::_loadSynthDef(std::string synthDefName)
{
  _oscm._loadSynthDef(synthDefName);
}

void Client_Server::_loadSynthDefDirectory(std::string dirName)
{
  _oscm._loadSynthDefDirectory(dirName);
}

void Client_Server::_setPort(const char *port)
{
   _port = port;
   _oscm._setPort(_port);
}

void Client_Server::_setHost(const char *host)
{
 
  _host = host;
  _oscm._setHost(_host);
}

const char* Client_Server::_getPort()
{
  return _oscm._getPort();
}


const char* Client_Server::_getHost()
{
  return _oscm._getHost();
}
