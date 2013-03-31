#include "Node.hpp"
#include <iostream>

#define T_NODE 1
#define T_GROUP 2


using namespace ColliderPlusPlus; 

Node::Node(Client_Server * other, const std::string& defName, int id_)
: id(id_), defName(defName), manuallyFreed(false)
{
  cs = other;
}

Node::~Node()
{
 
}

void Node::run()
{
  cs->runNode(id, 1);
  running = true;  
}


void Node::stop()
{
  cs->runNode(id, 0);   
  running = false; 
}


void Node::free()
{
  cs->freeNode(id);
  manuallyFreed = true;
}

void Node::query()
{
  cs->queryNode(id);
}

void Node::set(std::map<std::string, float> &controlVals)
{
  cs->setNodeControls(id, controlVals);
}

void Node::setn(std::map<std::string, float[]> &controlRanges)
{
 
}

void Node::busMap(std::map<std::string, Bus> &map)
{

}

Synth::Synth(Client_Server * other, const std::string& defName, 
				int id_, int initAction, int addAction, int target)
:Node(other, defName, id_)
{ 
  if(initAction == 0)
      getClientServer()->createPausedSynth(getDefName(), getId(), addAction, target);
  if(initAction == 1)
      getClientServer()->createSynth(getDefName(), getId(), addAction, target);
}

Synth::Synth(Client_Server * other, const std::string& defName, int id_,
     std::map<std::string,float> &args, int initAction, int addAction, int target)
:Node(other, defName, id_)
{ 
  if(initAction == 0)
     getClientServer()->createPausedSynth(getDefName(), getId(), args, addAction, target);
  if(initAction == 1)
     getClientServer()->createSynth(getDefName(), getId(), args, addAction, target);
}

Synth::~Synth()
{
  if(getId() != -1 && getId() >= 0 && getManuallyFreed() != true)
     getClientServer()->freeNode(getId());
}

Group::Group(Client_Server * other, const std::string& defName, int id_, int addAction, int target)
:Node(other, "Group", id_)
{
  getClientServer()->createGroup(getId());
}

Group::~Group()
{
  if(getId() != -1 && getId() >= 0 && getManuallyFreed() != true )
     getClientServer()->freeNode(getId());
}

void Group::freeAllSynths()
{
  getClientServer()->freeAllSynths(getId());	 
}

void Group::deepFreeAllSynths()
{
  getClientServer()->deepFreeAllSynths(getId());
}

RootNode::RootNode(Client_Server * other): Group(other, "Default", ROOT_NODE)
{
  
}

RootNode::~RootNode()
{

}
