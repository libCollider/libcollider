#include "Node.hpp"

using namespace ColliderPlusPlus; 

Node::Node()
{
 
}

Node::Node(int id): _id(id)
{
   Client_Server::_createNode(_id);
}

Node::~Node()
{

}

bool Node::_run()
{
  if(!Client_Server::_runNode(_id, 1))
    return false;

  _running = true; 

  return true; 
}


bool Node::_stop()
{
  if(!Client_Server::_runNode(_id, 0))
    return false;

  _running = false; 

  return true; 
}


bool Node::_free()
{
  if(!Client_Server::_freeNode(_id))
    return false;

  return true;
}

Synth::Synth(const std::string& defName, int id)
{
  _defName = defName;
  _id = id;
 
  Client_Server::_createSynth(_defName, _id);
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
