#include "Node.hpp"
#include <iostream>

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

void Node::_run(Client_Server &cs)
{
  cs._runNode(_id, 1);
  _running = true;  
}


void Node::_stop(Client_Server &cs)
{
  cs._runNode(_id, 0);   
  _running = false; 
}


void Node::_free(Client_Server &cs)
{
  cs._freeNode(_id);
}

void _busMap(std::map<std::string, Bus> &map)
{



}

Synth::Synth(Client_Server &cs, const std::string& defName, int id, int addAction, int target)
:Node(defName, id)
{ 
  cs._createSynth(_defName, _id, addAction, target);
}

Synth::Synth(Client_Server &cs, const std::string& defName, int id,
		 std::map<std::string,float> &args, int addAction, int target)
:Node(defName, id)
{ 
  cs._createSynth(_defName, _id, args, addAction, target);
}

Synth::~Synth()
{

}

Group::Group(Client_Server &cs, const std::string& defName, int id, int addAction, int target)
:Node("Group", id)
{
  cs._createGroup(_id);
}

Group::~Group()
{


}

void Group::_freeAllSynths(Client_Server &cs)
{
  cs._freeAllSynths(_id);	 
}

void Group::_deepFreeAllSynths(Client_Server &cs)
{
  cs._deepFreeAllSynths(_id);
}

RootNode::RootNode(Client_Server &cs): Group(cs, "Default", ROOT_NODE)
{
  
}

RootNode::~RootNode()
{

}
