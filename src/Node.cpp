#include "Node.hpp"

using namespace ColliderPlusPlus; 

/*Node::Node()
{
 
}*/

Node::Node(Client_Server &cs, int id): _id(id)
{
   cs._createNode(_id);
}

Node::Node(Client_Server &cs, const std::string& defName, int id): _id(id), _defName(defName)
{
   cs._createNode(_defName, _id);
}

Node::~Node()
{

}

bool Node::_run(Client_Server &cs)
{
  if(!cs._runNode(_id, 1))
    return false;

  _running = true; 

  return true; 
}


bool Node::_stop(Client_Server &cs)
{
  if(!cs._runNode(_id, 0))
    return false;

  _running = false; 

  return true; 
}


bool Node::_free(Client_Server &cs)
{
  if(!cs._freeNode(_id))
    return false;

  return true;
}

Synth::Synth(Client_Server &cs, const std::string& defName, int id): Node(cs, defName, id)
{ 

}

Synth::~Synth()
{

}

/*
Group::Group(const std::string& name, int id)
{
  _name = name;
  _id = id;

  Client_Server::_createGroup(_name, _id);
}

Group::~Group()
{

}

RootNode::RootNode(): Group("Default", 0)
{
  
}

RootNode::~RootNode()
{

}*/
