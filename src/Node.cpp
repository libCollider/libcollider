#include "Node.hpp"

using namespace ColliderPlusPlus; 

Node::Node(int id): _id(id), _running(true)
{
  
}

Node::~Node()
{

}

Synth::Synth(std::string defName, int id): Node(id)
{
  _defName = defName;
}

Synth::~Synth()
{

}

Group::Group(int id): Node(id)
{

}

Group::~Group()
{

}

RootNode::RootNode(): Group(0)
{
  
}

RootNode::~RootNode()
{

}
