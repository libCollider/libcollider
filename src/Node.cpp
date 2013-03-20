#include "Node.hpp"
#include <iostream>

#define T_NODE 1
#define T_GROUP 2


using namespace ColliderPlusPlus; 

Node::Node(Client_Server * cs, const std::string& defName, int id)
: _id(id), _defName(defName), _manuallyFreed(false)
{
  _cs = cs;
}

Node::~Node()
{
 
}

void Node::_run()
{
  _cs->_runNode(_id, 1);
  _running = true;  
}


void Node::_stop()
{
  _cs->_runNode(_id, 0);   
  _running = false; 
}


void Node::_free()
{
  _cs->_freeNode(_id);
  _manuallyFreed = true;
}

void Node::_query()
{
  _cs->_queryNode(_id);
}

void Node::_set(std::map<std::string, float> &controlVals)
{
  _cs->_setNodeControls(_id, controlVals);
}

void Node::_setn(std::map<std::string, float[]> &controlRanges)
{
 
}

void Node::_busMap(std::map<std::string, Bus> &map)
{

}

Synth::Synth(Client_Server * cs, const std::string& defName, 
				int id, int initAction, int addAction, int target)
:Node(cs, defName, id)
{ 
  if(initAction == 0)
      _getClientServer()->_createPausedSynth(_getDefName(), _getId(), addAction, target);
  if(initAction == 1)
      _getClientServer()->_createSynth(_getDefName(), _getId(), addAction, target);
}

Synth::Synth(Client_Server * cs, const std::string& defName, int id,
     std::map<std::string,float> &args, int initAction, int addAction, int target)
:Node(cs, defName, id)
{ 
  if(initAction == 0)
     _getClientServer()->_createPausedSynth(_getDefName(), _getId(), args, addAction, target);
  if(initAction == 1)
     _getClientServer()->_createSynth(_getDefName(), _getId(), args, addAction, target);
}

Synth::~Synth()
{
  if(_getId() != -1 && _getId() >= 0 && _getManuallyFreed() != true)
     _getClientServer()->_freeNode(_getId());
}

Group::Group(Client_Server * cs, const std::string& defName, int id, int addAction, int target)
:Node(cs, "Group", id)
{
  _getClientServer()->_createGroup(_getId());
}

Group::~Group()
{
  if(_getId() != -1 && _getId() >= 0 && _getManuallyFreed() != true )
     _getClientServer()->_freeNode(_getId());
}

void Group::_freeAllSynths()
{
  _getClientServer()->_freeAllSynths(_getId());	 
}

void Group::_deepFreeAllSynths()
{
  _getClientServer()->_deepFreeAllSynths(_getId());
}

RootNode::RootNode(Client_Server * cs): Group(cs, "Default", ROOT_NODE)
{
  
}

RootNode::~RootNode()
{

}
