#include "Node.hpp"

#define T_NODE 1
#define T_GROUP 2


using namespace ColliderPlusPlus; 

/*Node::Node()
{
 
}*/

Node::Node(Client_Server &cs, int id, int type): _id(id)
{
   cs._createNode(_id, type);
}

Node::Node(Client_Server &cs, const std::string& defName, int id, int type): _id(id), _defName(defName)
{
   cs._createNode(_defName, _id, type);
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

Synth::Synth(Client_Server &cs, const std::string& defName, int id): Node(cs, defName, id, T_NODE)
{ 

}

Synth::~Synth()
{

}


Group::Group(Client_Server &cs, const std::string& name, int id): Node(cs, name, id, T_GROUP)
{

}

Group::~Group()
{

}

RootNode::RootNode(Client_Server &cs): Group(cs, "Default", 0)
{
  
}

RootNode::~RootNode()
{

}
