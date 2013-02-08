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


//Public
std::string Client_Server::_getName()
{
  return _name; 
}


OscMessenger& Client_Server::_getOscMessenger()
{
  return _oscm;
}

void Client_Server::_boot()
{
  _oscm._boot();
}

int Client_Server::_nextNodeId()
{
   int firstNodeId = _pushFirstNodeId(_nextNode);
  _nextNode++;
    
  return firstNodeId;
}

void Client_Server::_dumpOSC(int toggle)
{
  _oscm._dumpOSC(toggle);
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



//Protected
bool Client_Server::_createNode(int nodeId)
{
   if(!_oscm._createNode(nodeId))
	return false;

   return true;
}

bool Client_Server::_createSynth(std::string name, int nodeId)
{
   if(!_oscm._createSynth(nodeId))
	return false;

   return true;
}

bool Client_Server::_createGroup(std::string name, int nodeId)
{
   if(!_oscm._createGroup(nodeId))
	return false;

   return true;
}

bool Client_Server::_runNode(int nodeId, int flag)
{
   if(!_oscm._runNode(nodeId, flag))
	return false;

   return true;
}

bool Client_Server::_freeNode(int nodeId)
{
  if(!_oscm._freeNode(nodeId))
	return false;

   return true;
}

void Client_Server::_quitServer()
{
  _oscm._quitServer();
}

bool Client_Server::_pingScsynth()
{
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



//Private
int Client_Server::_pushFirstNodeId(int nextNode)
{
  _nodeIDs.push_back(nextNode);
  return nextNode;
}
