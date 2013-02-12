#include "Node.hpp"

#define T_NODE 1
#define T_GROUP 2


using namespace ColliderPlusPlus; 

Node::Node()
:_id(0), _defName("Default")
{
 
}

Node::Node(const std::string& defName, int id)
: _id(id), _defName(defName)
{

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

Synth::Synth(Client_Server &cs, const std::string& defName, int id)
:Node(defName, id)
{ 
  cs._createSynth(_defName, _id);
}

Synth::Synth(Client_Server &cs, const std::string& defName, int id, std::map<std::string,float> &args)
:Node(defName, id)
{ 
  cs._createSynth(_defName, _id, args);
}

Synth::~Synth()
{

}

Group::Group(Client_Server &cs, const std::string& defName, int id)
:Node(defName, id)
{
  cs._createGroup(_defName, _id);
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
